#!/usr/bin/python3
# -*- coding: utf-8 -*-
##===-----------------------------------------------------------------------------*- Python -*-===##
##
##                                   S E R I A L B O X
##
## This file is distributed under terms of BSD license.
## See LICENSE.txt for more information.
##
##===------------------------------------------------------------------------------------------===##

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QWidget, QHBoxLayout, QVBoxLayout, QPushButton

from sdbcore.logger import Logger
from .errormessagebox import ErrorMessageBox
from .stencilfieldmetainfowidget import StencilFieldMetainfoWidget
from .stencilwidget import StencilWidget
from .tabstate import TabState


class StencilWindow(QWidget):
    def __init__(self, mainwindow, stencil_field_mapper, input_stencil_data,
                 reference_stencil_data):
        super().__init__()

        # Data
        self.__input_stencil_data = input_stencil_data
        self.__reference_stencil_data = reference_stencil_data
        self.__stencil_field_mapper = stencil_field_mapper

        # Widget
        self.__widget_mainwindow = mainwindow

        self.__widget_fieldmetainfo = StencilFieldMetainfoWidget()

        self.__widget_stencil_input = StencilWidget(self, self.__input_stencil_data,
                                                    self.__widget_fieldmetainfo)
        self.__widget_stencil_reference = StencilWidget(self, self.__reference_stencil_data,
                                                        self.__widget_fieldmetainfo)

        self.__widget_button_next = QPushButton("Next")
        self.__widget_button_next.clicked.connect(self.make_continue)
        self.__widget_button_next.setIcon(QIcon("sdbgui/images/run.png"))

        hbox_widgets = QHBoxLayout()
        hbox_widgets.addWidget(self.__widget_stencil_input)
        hbox_widgets.addWidget(self.__widget_stencil_reference)

        hbox_button = QHBoxLayout()
        hbox_button.addStretch(1)
        hbox_button.addWidget(self.__widget_button_next)

        vbox = QVBoxLayout()
        vbox.addLayout(hbox_widgets)
        vbox.addStretch(1)
        vbox.addWidget(self.__widget_fieldmetainfo)
        vbox.addLayout(hbox_button)
        self.setLayout(vbox)

    def match_fields(self):
        self.__stencil_field_mapper.match_fields()

    def make_continue(self):
        try:
            self.__stencil_field_mapper.compare_fields(self.__widget_stencil_input.fields,
                                                       self.__widget_stencil_reference.fields)
        except RuntimeError as e:
            ErrorMessageBox(self, str(e))
            return

        self.__widget_mainwindow.set_tab_highest_valid_state(TabState.Result)
        self.__widget_mainwindow.switch_to_tab(TabState.Result)

    def make_back(self):
        self.__widget_mainwindow.switch_to_tab(TabState.Setup)

    def make_update(self):
        Logger.info("Updating Stencil tab")
        self.__widget_stencil_input.make_update()
        self.__widget_stencil_reference.make_update()