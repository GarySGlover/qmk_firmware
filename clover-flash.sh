#!/bin/bash

qmk flash -kb handwired/clover -km default -bl uf2-split-left
qmk flash -kb handwired/clover -km default -bl uf2-split-right
