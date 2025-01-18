FROM debian:bullseye-slim

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    autotools-dev \
    autoconf \
    automake \
    libtool \
    pkg-config \
    libboost-all-dev \
    libicu-dev \
    liblcms2-dev \
    zlib1g-dev \
    libcppunit-dev \
    doxygen \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Clone libcdr and librevenge repositories
COPY third_party/libcdr /tmp/libcdr
COPY third_party/librevenge /tmp/librevenge


# Clone and build librevenge
RUN cd /tmp/librevenge && \
    ./autogen.sh && \
    ./configure --prefix=/usr/local --enable-shared && \
    make && \
    make install && \
    ldconfig && \
    # Create symlinks for librevenge libraries
    ln -s /usr/local/lib/librevenge-0.0.so.0 /usr/local/lib/librevenge.so && \
    ln -s /usr/local/lib/librevenge-generators-0.0.so.0 /usr/local/lib/librevenge-generators.so && \
    ln -s /usr/local/lib/librevenge-stream-0.0.so.0 /usr/local/lib/librevenge-stream.so && \
    rm -rf /tmp/librevenge

# Clone and build libcdr
RUN cd /tmp/libcdr && \
    ./autogen.sh && \
    ./configure --prefix=/usr/local --enable-shared && \
    make && \
    make install && \
    ldconfig && \
    # Create symlink for libcdr library
    ln -s /usr/local/lib/libcdr-0.1.so.1 /usr/local/lib/libcdr.so && \
    rm -rf /tmp/libcdr

# Add and compile the modified cdr2svg tool
COPY src/cdr2svg.cpp /tmp/cdr2svg.cpp
RUN g++ -o /usr/local/bin/cdr2svg /tmp/cdr2svg.cpp \
    -I/usr/local/include \
    -I/usr/local/include/libcdr-0.1 \
    -I/usr/local/include/librevenge-0.0 \
    -L/usr/local/lib \
    -Wl,-rpath,/usr/local/lib \
    -lcdr \
    -lrevenge \
    -lrevenge-generators \
    -lrevenge-stream \
    && chmod +x /usr/local/bin/cdr2svg

WORKDIR /app
CMD ["tail", "-f", "/dev/null"]