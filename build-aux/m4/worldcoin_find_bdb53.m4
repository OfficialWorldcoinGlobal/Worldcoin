AC_DEFUN([WORLDCOIN_FIND_BDB53],[
  AC_MSG_CHECKING([for Berkeley DB C++ headers])
  BDB_CPPFLAGS=
  BDB_LIBS=
  bdbpath=X
  bdb53path=X
  bdbdirlist=
  for _vn in 5.3 53 5 ''; do
    for _pfx in b lib ''; do
      bdbdirlist="$bdbdirlist ${_pfx}db${_vn}"
    done
  done
  for searchpath in $bdbdirlist ''; do
    test -n "${searchpath}" && searchpath="${searchpath}/"
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
      #include <${searchpath}db_cxx.h>
    ]],[[
      #if !((DB_VERSION_MAJOR == 5 && DB_VERSION_MINOR >= 3) || DB_VERSION_MAJOR > 5)
        #error "failed to find bdb 5.3"
      #endif
    ]])],[
      if test "x$bdbpath" = "xX"; then
        bdbpath="${searchpath}"
      fi
    ],[
      continue
    ])
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
      #include <${searchpath}db_cxx.h>
    ]],[[
      #if !(DB_VERSION_MAJOR == 5 && DB_VERSION_MINOR == 3)
        #error "failed to find bdb 5.3"
      #endif
    ]])],[
      bdb53path="${searchpath}"
      break
    ],[])
  done
  if test "x$bdbpath" = "xX"; then
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([libdb_cxx headers missing, Worldcoin Core requires this library for wallet functionality (--disable-wallet to disable wallet functionality)])
  elif test "x$bdb53path" = "xX"; then
    WORLDCOIN_SUBDIR_TO_INCLUDE(BDB_CPPFLAGS,[${bdbpath}],db_cxx)
    AC_ARG_WITH([incompatible-bdb],[AS_HELP_STRING([--with-incompatible-bdb], [allow using a bdb version other than 5.1])],[
      AC_MSG_WARN([Found Berkeley DB other than 5.1; wallets opened by this build will not be portable!])
    ],[
      AC_MSG_ERROR([Found Berkeley DB other than 5.1, required for portable wallets (--with-incompatible-bdb to ignore or --disable-wallet to disable wallet functionality)])
    ])
  else
    WORLDCOIN_SUBDIR_TO_INCLUDE(BDB_CPPFLAGS,[${bdb53path}],db_cxx)
    bdbpath="${bdb53path}"
  fi
  AC_SUBST(BDB_CPPFLAGS)
  
  # TODO: Ideally this could find the library version and make sure it matches the headers being used
  for searchlib in db_cxx-5.3 db_cxx; do
    AC_CHECK_LIB([$searchlib],[main],[
      BDB_LIBS="-l${searchlib}"
      break
    ])
  done
  if test "x$BDB_LIBS" = "x"; then
      AC_MSG_ERROR([libdb_cxx missing, Worldcoin Core requires this library for wallet functionality (--disable-wallet to disable wallet functionality)])
  fi
  AC_SUBST(BDB_LIBS)
])
