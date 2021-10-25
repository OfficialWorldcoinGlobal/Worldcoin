A guide for building on CentOS 8
------------------------------------------

```
sudo yum install -y gcc-c++ git make tar wget patch epel-release bzip2 automake autoconf  \
libtool python2 python36 boost-devel openssl openssl-devel libevent-devel

cd ~
git clone https://github.com/Worldcoin-Network/Worldcoin.git
cd ~/Worldcoin/depends
PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') 
make NO_QT=1
cd sources
tar -xvzf db*.NC.tar.gz
cd db*.NC
sed -i 's/__atomic_compare_exchange/__atomic_compare_exchange_db/g' ./src/dbinc/atomic.h
cd build_unix
../dist/configure --prefix=/usr/local --enable-cxx
make
sudo make install

cd ~/Worldcoin
./autogen.sh
CONFIG_SITE=$PWD/depends/*linux*/share/config.site ./configure --without-gui --disable-tests --disable-man --prefix=/
make
cd src
strip worldcoind
strip worldcoin-cli
strip worldcoin-tx

```

Install (optional)
------------------------------------------
```
cd ~/Worldcoin/src
sudo make install
```

Run daemon
------------------------------------------
```
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib"
worldcoind --daemon
```

Command-line client
------------------------------------------
```
worldcoin-cli
```
