APPLICATION = ccnl_riot

# if no BOARD is found in the environment, use this default:
BOARD ?= native

BOARD_WHITELIST := fox iotlab-m3 msba2 mulle native pba-d-01-kw2x samr21-xpro


# set to the absolute path to the RIOT base directory
RIOTBASE ?= $(CURDIR)/../../riot

CFLAGS += -DDEVELHELP
CFLAGS += -DUSE_LINKLAYER
CFLAGS += -DCCNL_UAPI_H_
CFLAGS += -DUSE_SUITE_NDNTLV
CFLAGS += -DNEEDS_PREFIX_MATCHING
CFLAGS += -DNEEDS_PACKET_CRAFTING
CFLAGS += -DUSE_HMAC256
CFLAGS += -DUSE_STATS
CFLAGS += -DUSE_RONR

# change this to 0 show compiler invocation lines by default:
QUIET ?= 1

USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
# include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netif_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += timex
USEMODULE += xtimer
USEMODULE += random
USEMODULE += prng_minstd

USEPKG += tlsf

USEPKG += ccn-lite
USEMODULE += ccn-lite-utils

include $(RIOTBASE)/Makefile.include
