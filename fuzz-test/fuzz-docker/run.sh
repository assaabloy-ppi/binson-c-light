#!/bin/sh

sudo docker run -it --cap-add=SYS_PTRACE -v $(pwd)/../../:/home/developer/binson-c-light binson-development