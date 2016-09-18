//===-- Core/StorageViewIterator.cpp ------------------------------------------------*- C++ -*-===//
//
//                                    S E R I A L B O X
//
// This file is distributed under terms of BSD license.
// See LICENSE.txt for more information
//
//===------------------------------------------------------------------------------------------===//
//
/// \file
/// This file provides an Iterator interface for the StorageView.
///
//===------------------------------------------------------------------------------------------===//

#include "serialbox/Core/Compiler.h"
#include "serialbox/Core/StorageView.h"
#include "serialbox/Core/StorageViewIterator.h"

namespace serialbox {

StorageViewIterator::StorageViewIterator(const StorageView* storageView, bool beginning)
    : bytesPerElement_(storageView->bytesPerElement()), storageView_(storageView) {

  if(!(end_ = !beginning)) {
    index_.resize(storageView_->dims().size(), 0);
    orignPtr_ = const_cast<StorageView*>(storageView_)->originPtr();  // TODO: fix this const cast
    curPtr_ = orignPtr_ + computeCurrentIndex();
  }
}

StorageViewIterator::iterator& StorageViewIterator::operator++() noexcept {
  if(!end_) {
    // Consecutively increment the dimensions (column-major order)
    int size = index_.size();
    for(int i = 0; i < size; ++i)
      if(SERIALBOX_BUILTIN_LIKELY(++index_[i] < storageView_->dims()[i]))
        break;
      else {
        index_[i] = 0;
        // If we overflow in the last dimension we reached the end
        if(SERIALBOX_BUILTIN_UNLIKELY(i == size - 1))
          end_ = true;
      }

    // Compute the current data pointer
    curPtr_ = orignPtr_ + computeCurrentIndex();
  }
  return (*this);
}

bool StorageViewIterator::operator==(const iterator& right) const noexcept { 
  return (curPtr_ == right.curPtr_ || (end_ == true && end_ == right.end_)); 
}

void StorageViewIterator::swap(StorageViewIterator& other) noexcept {
  std::swap(curPtr_, other.curPtr_);
  index_.swap(other.index_);
  std::swap(bytesPerElement_, other.bytesPerElement_);
  std::swap(storageView_, other.storageView_);
}

std::ostream& operator<<(std::ostream& stream, const StorageViewIterator& it) {
  stream << "StorageViewIterator = {\n";
  stream << "  originPtr: " << static_cast<void*>(it.curPtr_) << "\n";
  stream << "  curPtr: " << it.end_ << "\n";
  stream << "  index: [";
  for(auto i : it.index_)
    stream << " " << i;
  stream << " ]\n  end: " << std::boolalpha << it.end_ << "\n";
  stream << "  bytesPerElement: " << it.bytesPerElement_ << "\n";
  stream << "  storageView: " << std::hex << it.storageView_ << "\n";
  stream << "}\n";
  return stream;
}

int StorageViewIterator::computeCurrentIndex() const noexcept {
  int pos = 0;
  const int size = index_.size();
  for(int i = 0; i < size; ++i)
    pos += bytesPerElement_ * (storageView_->strides()[i] * index_[i]);
  return pos;
}

} // namespace serialbox