package=zeromq
$(package)_version=4.1.5
$(package)_download_path=https://github.com/zeromq/zeromq4-1/releases/download/v$($(package)_version)/
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=04aac57f081ffa3a2ee5ed04887be9e205df3a7ddade0027460b8042432bdbcf
$(package)_patches=enable_static_libraries.patch fix_autotools_static_builds.patch

define $(package)_set_vars
  $(package)_config_opts=--without-documentation --disable-shared --without-libsodium --disable-curve
  $(package)_config_opts_linux=--with-pic
  $(package)_cxxflags=-std=c++11
endef

define $(package)_preprocess_cmds
  patch -p1 < $($(package)_patch_dir)/enable_static_libraries.patch && \
  patch -p1 < $($(package)_patch_dir)/fix_autotools_static_builds.patch && \
  ./autogen.sh
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE) libzmq.la
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install-libLTLIBRARIES install-includeHEADERS install-pkgconfigDATA
endef

define $(package)_postprocess_cmds
  rm -rf bin share
endef