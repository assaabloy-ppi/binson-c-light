FROM base/archlinux:latest
RUN pacman -Syy --noconfirm
RUN pacman -Su --noconfirm
RUN pacman -Sy gcc gdb lib32-gcc-libs wget clang make screen llvm llvm-libs gcc-multilib nano cmake nano git jdk8-openjdk libsodium valgrind cppcheck --noconfirm
RUN wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
RUN tar -xf afl-latest.tgz && rm afl-latest.tgz && mv afl-* afl-latest
WORKDIR "afl-latest"
RUN CC=clang CXX=clang++ make && LLVM_CONFIG=llvm-config CC=clang CXX=clang++ make -C llvm_mode
RUN LLVM_CONFIG=llvm-config CC=clang CXX=clang++ make install
WORKDIR "/home/developer"
RUN wget http://trust-in-soft.com/tis-interpreter-2016-05.linux-x86_64.tar.gz
RUN tar -xf tis-interpreter-2016-05.linux-x86_64.tar.gz
WORKDIR "/home/developer"
RUN git clone https://github.com/linux-test-project/lcov && make -C lcov install && rm -rf lcov
ENTRYPOINT ["bash"]