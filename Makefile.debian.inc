CRYPTO_OBJS =                               \
       ./src/gnb_keys.o                     \
       ./src/gnb_binary.o                   \
       ./libs/ed25519/add_scalar.o          \
       ./libs/ed25519/fe.o                  \
       ./libs/ed25519/ge.o                  \
       ./libs/ed25519/key_exchange.o        \
       ./libs/ed25519/keypair.o             \
       ./libs/ed25519/sc.o                  \
       ./libs/ed25519/seed.o                \
       ./libs/ed25519/sha512.o              \
       ./libs/ed25519/sign.o                \
       ./libs/ed25519/verify.o              \
       ./src/crypto/arc4/arc4.o             \
       ./src/crypto/random/gnb_random.o


GNB_OBJS =                                 \
       ./src/gnb_svr.o                     \
       ./src/gnb_daemon.o                  \
       ./src/gnb_worker.o                  \
       ./src/gnb_ctl_block.o               \
       ./src/gnb_address.o                 \
       ./src/gnb_main_worker.o             \
       ./src/gnb_node_worker.o             \
       ./src/gnb_index_worker.o            \
       ./src/gnb_index_service_worker.o    \
       ./src/gnb_detect_worker.o           \
       ./src/gnb_conf.o                    \
       ./src/gnb_conf_file.o               \
       ./src/gnb_config_lite.o             \
       ./src/gnb_node.o                    \
       ./src/gnb_udp.o                     \
       ./src/gnb_payload16.o               \
       ./src/gnb_ring_buffer.o             \
       ./src/gnb_time.o                    \
       ./src/gnb_lru32.o                   \
       ./src/gnb_fixed_pool.o              \
       ./src/gnb_doubly_linked_list.o      \
       ./src/gnb_alloc.o                   \
       ./src/gnb_mmap.o                    \
       ./src/gnb_dir.o                     \
       ./src/gnb_arg_list.o                \
       ./src/gnb_log.o                     \
       ./src/gnb_hash32.o                  \
       ./libs/hash/murmurhash.o


GNB_PF_OBJS   =                                  \
      ./src/gnb_pf.o                             \
      ./src/packet_filter/gnb_pf_route.o         \
      ./src/packet_filter/gnb_pf_crypto_xor.o    \
      ./src/packet_filter/gnb_pf_crypto_arc4.o   \
      ./src/packet_filter/gnb_pf_dump.o


GNB_ES_OBJS =                             \
      ./src/cli/gnb_es.o                  \
      ./src/es/gnb_environment_service.o  \
      ./src/gnb_daemon.o                  \
      ./src/es/gnb_es_dump.o              \
      ./src/es/gnb_es_broadcast_address.o \
      ./src/es/gnb_es_resolv.o            \
      ./src/es/gnb_es_upnp.o              \
      ./src/gnb_ctl_block.o               \
      ./src/gnb_binary.o                  \
      ./src/gnb_time.o                    \
      ./src/gnb_address.o                 \
      ./src/gnb_payload16.o               \
      ./src/gnb_udp.o                     \
      ./src/gnb_log.o                     \
      ./src/gnb_alloc.o                   \
      ./src/gnb_mmap.o                    \
      ./src/gnb_hash32.o                  \
      ./libs/hash/murmurhash.o


GNB_CTL_OBJS =                            \
       ./src/cli/gnb_ctl.o                \
       ./src/ctl/gnb_ctl_dump.o           \
       ./src/gnb_ctl_block.o              \
       ./src/gnb_ctl_block_set.o          \
       ./src/gnb_binary.o                 \
       ./src/gnb_time.o                   \
       ./src/gnb_address.o                \
       ./src/gnb_payload16.o              \
       ./src/gnb_udp.o                    \
       ./src/gnb_mmap.o                   \
       ./libs/ed25519/sha512.o


GNB_OBJS    += ./src/gnb_mod_register.o
GNB_ES_OBJS += ./src/es/gnb_es_platform.o
      
