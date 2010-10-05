#!/bin/bash

python setup.py realclean
python setup.py build_ext -i
python setup.py test
