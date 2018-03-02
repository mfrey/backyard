This is an example for the discussion on CCN-lite issue [#207](https://github.com/cn-uofbasel/ccn-lite/issues/207).

## Pre-Configuration
The code in this directory makes use of CCN-lites new API, hence the ``PKG_VERSION`` and the build flags at ``git-download`` target need to be changed, i.e.
```
PKG_NAME=ccn-lite
PKG_URL=https://github.com/cn-uofbasel/ccn-lite/
PKG_VERSION=08e0a22d609caa912878a7c1fc724fae371b4b6b
PKG_LICENSE=ISC

.PHONY: all

export RIOT_CFLAGS = ${CFLAGS} ${INCLUDES}

all: git-download
        cd $(PKG_BUILDDIR)/src && cmake -DCCNL_RIOT=1 -DRIOT_CFLAGS="${RIOT_CFLAGS}" -DBUILD_TESTING=OFF \
         . && make
        cp $(PKG_BUILDDIR)/src/lib/libccnl-riot.a ${BINDIR}/ccn-lite.a

include $(RIOTBASE)/pkg/pkg.mk
```

## Install
1. Clone the repository into your ``${RIOTBASE}/examples/`` directory.
2. Compile the code with  (replace ``pba-d-01-kw2x`` with the acutal RIOT supported board you are going to use)
```bash
$ BOARD="pba-d-01-kw2x" make
```
3. Flash it to your target via
```bash
$ BOARD="pba-d-01-kw2x" make flash
```

## Usage
In your RIOT shell, start CCN-lite by
```bash
# ccnl_open 3
```
(replace 3 with the actual interface id of your network interface) and create an interest via
```bash
# ccnl_int /foo/bar
```
