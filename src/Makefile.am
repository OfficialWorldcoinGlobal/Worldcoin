# Copyright (c) 2013-2016 The Worldcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

WORLDCOIN_INCLUDES=-I$(builddir) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

WORLDCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
WORLDCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBWORLDCOIN_SERVER=libworldcoin_server.a
LIBWORLDCOIN_COMMON=libworldcoin_common.a
LIBWORLDCOIN_CONSENSUS=libworldcoin_consensus.a
LIBWORLDCOIN_CLI=libworldcoin_cli.a
LIBWORLDCOIN_UTIL=libworldcoin_util.a
LIBWORLDCOIN_CRYPTO_BASE=crypto/libworldcoin_crypto_base.a
LIBWORLDCOINQT=qt/libworldcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBWORLDCOIN_ZMQ=libworldcoin_zmq.a
endif
if BUILD_WORLDCOIN_LIBS
LIBWORLDCOINCONSENSUS=libworldcoinconsensus.la
endif
if ENABLE_WALLET
LIBWORLDCOIN_WALLET=libworldcoin_wallet.a
endif

LIBWORLDCOIN_CRYPTO= $(LIBWORLDCOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBWORLDCOIN_CRYPTO_SSE41 = crypto/libworldcoin_crypto_sse41.a
LIBWORLDCOIN_CRYPTO += $(LIBWORLDCOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBWORLDCOIN_CRYPTO_AVX2 = crypto/libworldcoin_crypto_avx2.a
LIBWORLDCOIN_CRYPTO += $(LIBWORLDCOIN_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBWORLDCOIN_CRYPTO_SHANI = crypto/libworldcoin_crypto_shani.a
LIBWORLDCOIN_CRYPTO += $(LIBWORLDCOIN_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBWORLDCOIN_CRYPTO) \
  $(LIBWORLDCOIN_UTIL) \
  $(LIBWORLDCOIN_COMMON) \
  $(LIBWORLDCOIN_CONSENSUS) \
  $(LIBWORLDCOIN_SERVER) \
  $(LIBWORLDCOIN_CLI) \
  $(LIBWORLDCOIN_WALLET) \
  $(LIBWORLDCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBWORLDCOINCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_WORLDCOIND
  bin_PROGRAMS += worldcoind
endif

if BUILD_WORLDCOIN_UTILS
  bin_PROGRAMS += worldcoin-cli worldcoin-tx
endif

.PHONY: FORCE check-symbols check-security
# worldcoin core #
WORLDCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  auxpow.h \
  base58.h \
  bech32.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  worldcoin.cpp \
  worldcoin.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  index/base.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  interfaces/handler.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/auxpow_miner.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/rawtransaction.h \
  rpc/register.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/ismine.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  shutdown.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmemory.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  walletinitinterface.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/walletutil.h \
  wallet/coinselection.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libworldcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between worldcoind and worldcoin-qt
libworldcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libworldcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libworldcoin_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/tx_verify.cpp \
  httprpc.cpp \
  httpserver.cpp \
  index/base.cpp \
  index/txindex.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  outputtype.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  policy/rbf.cpp \
  pow.cpp \
  rest.cpp \
  rpc/auxpow_miner.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  rpc/util.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(WORLDCOIN_CORE_H)

if ENABLE_ZMQ
libworldcoin_zmq_a_CPPFLAGS = $(WORLDCOIN_INCLUDES) $(ZMQ_CFLAGS)
libworldcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libworldcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp
endif


# wallet: shared between worldcoind and worldcoin-qt, but only linked
# when wallet enabled
libworldcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES)
libworldcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libworldcoin_wallet_a_SOURCES = \
  interfaces/wallet.cpp \
  wallet/coincontrol.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/init.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(WORLDCOIN_CORE_H)

# crypto primitives library
crypto_libworldcoin_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libworldcoin_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libworldcoin_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/scrypt.cpp \
  crypto/scrypt.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

if USE_ASM
crypto_libworldcoin_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libworldcoin_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libworldcoin_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libworldcoin_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libworldcoin_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libworldcoin_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libworldcoin_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libworldcoin_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libworldcoin_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libworldcoin_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libworldcoin_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libworldcoin_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libworldcoin_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libworldcoin_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libworldcoin_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libworldcoin_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libworldcoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES)
libworldcoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libworldcoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/pureheader.cpp \
  primitives/pureheader.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/worldcoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between worldcoind, and worldcoin-qt and non-server tools
libworldcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES)
libworldcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libworldcoin_common_a_SOURCES = \
  auxpow.cpp \
  base58.cpp \
  bech32.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  key_io.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  policy/feerate.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/ismine.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(WORLDCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libworldcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES)
libworldcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libworldcoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/handler.cpp \
  interfaces/node.cpp \
  logging.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(WORLDCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libworldcoin_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between worldcoin-cli and worldcoin-qt
libworldcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES)
libworldcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libworldcoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(WORLDCOIN_CORE_H)

nodist_libworldcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# worldcoind binary #
worldcoind_SOURCES = worldcoind.cpp
worldcoind_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES)
worldcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
worldcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
worldcoind_SOURCES += worldcoind-res.rc
endif

worldcoind_LDADD = \
  $(LIBWORLDCOIN_SERVER) \
  $(LIBWORLDCOIN_WALLET) \
  $(LIBWORLDCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBWORLDCOIN_UTIL) \
  $(LIBWORLDCOIN_ZMQ) \
  $(LIBWORLDCOIN_CONSENSUS) \
  $(LIBWORLDCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

worldcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# worldcoin-cli binary #
worldcoin_cli_SOURCES = worldcoin-cli.cpp
worldcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES) $(EVENT_CFLAGS)
worldcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
worldcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
worldcoin_cli_SOURCES += worldcoin-cli-res.rc
endif

worldcoin_cli_LDADD = \
  $(LIBWORLDCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBWORLDCOIN_UTIL) \
  $(LIBWORLDCOIN_CRYPTO)

worldcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# worldcoin-tx binary #
worldcoin_tx_SOURCES = worldcoin-tx.cpp
worldcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(WORLDCOIN_INCLUDES)
worldcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
worldcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
worldcoin_tx_SOURCES += worldcoin-tx-res.rc
endif

worldcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBWORLDCOIN_COMMON) \
  $(LIBWORLDCOIN_UTIL) \
  $(LIBWORLDCOIN_CONSENSUS) \
  $(LIBWORLDCOIN_CRYPTO) \
  $(LIBSECP256K1)

worldcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# worldcoinconsensus library #
if BUILD_WORLDCOIN_LIBS
include_HEADERS = script/worldcoinconsensus.h
libworldcoinconsensus_la_SOURCES = $(crypto_libworldcoin_crypto_base_a_SOURCES) $(libworldcoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libworldcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libworldcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libworldcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libworldcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_WORLDCOIN_INTERNAL
libworldcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/worldcoin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/worldcoin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/worldcoin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/worldcoin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
