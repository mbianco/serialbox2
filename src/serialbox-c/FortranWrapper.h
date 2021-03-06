/*===-- serialbox-c/FortranWrapper.h ------------------------------------------------*- C++ -*-===*\
 *
 *                                    S E R I A L B O X
 *
 * This file is distributed under terms of BSD license.
 * See LICENSE.txt for more information
 *
 *===------------------------------------------------------------------------------------------===//
 *
 *! \file
 *! This file contains some abstractions for the Fortran interface.
 *
\*===------------------------------------------------------------------------------------------===*/

#ifndef SERIALBOX_C_FORTRANWRAPPER_H
#define SERIALBOX_C_FORTRANWRAPPER_H

/**
 * \ingroup serialboxC
 * @{
 *
 * \defgroup fortran_wrapper Fortran wrapper methods
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*===------------------------------------------------------------------------------------------===*\
 *     Serializer
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Wrapper for \ref serialboxSerializerWrite
 */
void serialboxFortranSerializerWrite(void* serializer, const void* savepoint, const char* name,
                                     void* originPtr, int istride, int jstride, int kstride,
                                     int lstride);

/**
 * \brief Wrapper for \ref serialboxSerializerRead
 */
void serialboxFortranSerializerRead(void* serializer, const void* savepoint, const char* name,
                                    void* originPtr, int istride, int jstride, int kstride,
                                    int lstride);

/**
 * \brief Print debug information (i.e convert serializer to string)
 */
void serialboxFortranSerializerPrintDebugInfo(void* serializer);

/**
 * \brief Perform consistency checks concerning dimensions and type of the field `name`
 */
void serialboxFortranSerializerCheckField(const void* serializer, const char* name, int* type,
                                          int* isize, int* jsize, int* ksize, int* lsize);

/**
 * \brief Compute unit-strides of registered field `fieldname`
 */
void serialboxFortranComputeStrides(void* serializer, const char* fieldname, const void* basePtr,
                                    const void* iplus1, const void* jplus1, const void* kplus1,
                                    const void* lplus1, int* istride, int* jstride, int* kstride,
                                    int* lstride);

/**
 * \brief Add a global meta-information `key=value` pair to the Serializer
 *
 * This function corresponds to `fs_add_serializer_metainfo_X`
 *
 * \param serializer  Serializer to use
 * \param key         Key of the new element
 * \param value       Object to be copied to the value of the new element
 * @{
 */
void serialboxFortranSerializerAddMetainfoBoolean(void* serializer, const char* key, int value);
void serialboxFortranSerializerAddMetainfoInt32(void* serializer, const char* key, int value);
void serialboxFortranSerializerAddMetainfoFloat32(void* serializer, const char* key, float value);
void serialboxFortranSerializerAddMetainfoFloat64(void* serializer, const char* key, double value);
void serialboxFortranSerializerAddMetainfoString(void* serializer, const char* key,
                                                 const char* value);
/** @} */

/**
 * \brief Register `field` within the serializer
 *
 * This function corresponds to `fs_register_field`
 *
 * \param serializer        Serializer to use
 * \param name              The name of the field
 * \param type              TypeID of the field (\ref serialboxTypeID)
 * \param bytesPerElement   The size in bytes of a scalar value (e.g. 8 for doubles)
 * \param iSize             The size of the first dimension
 * \param jSize             The size of the second dimension
 * \param kSize             The size of the third dimension
 * \param lsize             The size of the fourth dimension
 * \param iMinusHalo        The dimension of the halo in negative i-direction
 * \param iPlusHalo         The dimension of the halo in positive i-direction
 * \param jMinusHalo        The dimension of the halo in negative j-direction
 * \param jPlusHalo         The dimension of the halo in positive j-direction
 * \param kMinusHalo        The dimension of the halo in negative k-direction
 * \param kPlusHalo         The dimension of the halo in positive k-direction
 * \param lMinusHalo        The dimension of the halo in negative l-direction
 * \param lPlusHalo         The dimension of the halo in positive l-direction
 */
void serialboxFortranSerializerRegisterField(void* serializer, const char* name, int type,
                                             int bytesPerElement, int iSize, int jSize, int kSize,
                                             int lSize, int iMinusHalo, int iPlusHalo,
                                             int jMinusHalo, int jPlusHalo, int kMinusHalo,
                                             int kPlusHalo, int lMinusHalo, int lPlusHalo);

/*===------------------------------------------------------------------------------------------===*\
 *     FieldMetainfoImpl
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Add a meta-information `key=value` pair to `field` of the serializer
 *
 * This function corresponds to `fs_add_field_metainfo_i`
 *
 * \param serializer  Serializer to use
 * \param field       Name of the field
 * \param key         Key of the new element
 * \param value       Object to be copied to the value of the new element
 * @{
 */
void serialboxFortranSerializerAddFieldMetainfoBoolean(void* serializer, const char* field,
                                                       const char* key, int value);
void serialboxFortranSerializerAddFieldMetainfoInt32(void* serializer, const char* field,
                                                     const char* key, int value);
void serialboxFortranSerializerAddFieldMetainfoFloat32(void* serializer, const char* field,
                                                       const char* key, float value);
void serialboxFortranSerializerAddFieldMetainfoFloat64(void* serializer, const char* field,
                                                       const char* key, double value);
void serialboxFortranSerializerAddFieldMetainfoString(void* serializer, const char* field,
                                                      const char* key, const char* value);
/** @} */

/*===------------------------------------------------------------------------------------------===*\
 *     Savepoint
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Add a meta-information `key=value` pair to the `savepoint`
 *
 * This function corresponds to `fs_add_savepoint_metainfo_f`
 *
 * \param savepoint   Savepoint to use
 * \param key         Key of the new element
 * \param value       Object to be copied to the value of the new element
 * @{
 */
void serialboxFortranSavepointAddMetainfoBoolean(void* savepoint, const char* key, int value);
void serialboxFortranSavepointAddMetainfoInt32(void* savepoint, const char* key, int value);
void serialboxFortranSavepointAddMetainfoFloat32(void* savepoint, const char* key, float value);
void serialboxFortranSavepointAddMetainfoFloat64(void* savepoint, const char* key, double value);
void serialboxFortranSavepointAddMetainfoString(void* savepoint, const char* key,
                                                const char* value);
/** @} */

/** @} @} */

#ifdef __cplusplus
}
#endif

#endif
