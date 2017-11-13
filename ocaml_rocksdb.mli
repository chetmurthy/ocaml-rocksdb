module DBOptionsST :
  sig
    type t = {
      create_if_missing : bool;
      create_missing_column_families : bool;
      error_if_exists : bool;
      paranoid_checks : bool;
      info_log_level : char;
      max_open_files : int;
      max_file_opening_threads : int;
      max_total_wal_size : int64;
      use_fsync : bool;
      db_log_dir : string;
      wal_dir : string;
      delete_obsolete_files_period_micros : int64;
      max_background_jobs : int;
      base_background_compactions : int;
      max_background_compactions : int;
      max_subcompactions : int32;
      max_background_flushes : int;
      max_log_file_size : int;
      log_file_time_to_roll : int;
      keep_log_file_num : int;
      recycle_log_file_num : int;
      max_manifest_file_size : int64;
      table_cache_numshardbits : int;
      _WAL_ttl_seconds : int64;
      _WAL_size_limit_MB : int64;
      manifest_preallocation_size : int;
      allow_mmap_reads : bool;
      allow_mmap_writes : bool;
      use_direct_reads : bool;
      use_direct_io_for_flush_and_compaction : bool;
      allow_fallocate : bool;
      is_fd_close_on_exec : bool;
      skip_log_error_on_recovery : bool;
      stats_dump_period_sec : int;
      advise_random_on_open : bool;
      db_write_buffer_size : int;
      access_hint_on_compaction_start : int;
      new_table_reader_for_compaction_inputs : bool;
      compaction_readahead_size : int;
      random_access_max_buffer_size : int;
      writable_file_max_buffer_size : int;
      use_adaptive_mutex : bool;
      bytes_per_sync : int64;
      wal_bytes_per_sync : int64;
      enable_thread_tracking : bool;
      delayed_write_rate : int64;
      enable_pipelined_write : bool;
      allow_concurrent_memtable_write : bool;
      enable_write_thread_adaptive_yield : bool;
      write_thread_max_yield_usec : int64;
      write_thread_slow_yield_usec : int64;
      skip_stats_update_on_db_open : bool;
      wal_recovery_mode : char;
      allow_2pc : bool;
      fail_if_options_file_error : bool;
      dump_malloc_stats : bool;
      avoid_flush_during_recovery : bool;
      avoid_flush_during_shutdown : bool;
      allow_ingest_behind : bool;
      concurrent_prepare : bool;
      manual_wal_flush : bool;
    }
  end
module Types :
  sig
    type dboptions = DBOptionsST.t
    and writebatch_id
    and iterator_id
    and cfd = string * cfoptions_id
    and comparator_id
    and woptions_id
    and roptions_id
    and cfoptions_id
    and dboptions_id
    and options_id
    and db_id_opt = db_id option
    and db_id
    and cfhandle_id
    and status = Rocks_types.status_t
    and size_t = int
  end
external rocksdb_cfoptions_create : unit -> Types.cfoptions_id
  = "rocksdb_cfoptions_create"
external rocksdb_cfoptions_destroy : Types.cfoptions_id -> unit
  = "rocksdb_cfoptions_destroy"
external rocksdb_roptions_create : unit -> Types.roptions_id
  = "rocksdb_roptions_create"
external rocksdb_roptions_destroy : Types.roptions_id -> unit
  = "rocksdb_roptions_destroy"
external rocksdb_woptions_create : unit -> Types.woptions_id
  = "rocksdb_woptions_create"
external rocksdb_woptions_destroy : Types.woptions_id -> unit
  = "rocksdb_woptions_destroy"
external rocksdb_dboptions_create : unit -> Types.dboptions_id
  = "rocksdb_dboptions_create"
external rocksdb_dboptions_destroy : Types.dboptions_id -> unit
  = "rocksdb_dboptions_destroy"
external rocksdb_list_column_families :
  Types.dboptions_id -> string -> Rocks_types.status_t * string array
  = "rocksdb_list_column_families"
external rocksdb_bytewise_comparator_create : unit -> Types.comparator_id
  = "rocksdb_bytewise_comparator_create"
external rocksdb_reverse_bytewise_comparator_create :
  unit -> Types.comparator_id = "rocksdb_reverse_bytewise_comparator_create"
external rocksdb_myrocks_comparator_create : unit -> Types.comparator_id
  = "rocksdb_myrocks_comparator_create"
external rocksdb_rev_myrocks_comparator_create : unit -> Types.comparator_id
  = "rocksdb_rev_myrocks_comparator_create"
external rocksdb_cfoptions_set_comparator :
  Types.cfoptions_id -> Types.comparator_id -> unit
  = "rocksdb_cfoptions_set_comparator"
external rocksdb_options_create : unit -> Types.options_id
  = "rocksdb_options_create"
external rocksdb_options_destroy : Types.options_id -> unit
  = "rocksdb_options_destroy"
external rocksdb_open :
  Types.options_id -> string -> Rocks_types.status_t * Types.db_id option
  = "rocksdb_open"
external rocksdb_open_column_families :
  Types.dboptions_id ->
  string ->
  (string * Types.cfoptions_id) array ->
  Rocks_types.status_t * Types.cfhandle_id array * Types.db_id option
  = "rocksdb_open_column_families"
external rocksdb_open_for_readonly :
  Types.options_id ->
  string -> bool -> Rocks_types.status_t * Types.db_id option
  = "rocksdb_open_for_readonly"
external rocksdb_open_column_families_for_readonly :
  Types.dboptions_id ->
  string ->
  (string * Types.cfoptions_id) array ->
  bool -> Rocks_types.status_t * Types.cfhandle_id array * Types.db_id option
  = "rocksdb_open_column_families_for_readonly"
external rocksdb_create_column_family :
  Types.db_id ->
  Types.cfoptions_id -> string -> Rocks_types.status_t * Types.cfhandle_id
  = "rocksdb_create_column_family"
external rocksdb_drop_column_family :
  Types.db_id -> Types.cfhandle_id -> Rocks_types.status_t
  = "rocksdb_drop_column_family"
external rocksdb_cfhandle_destroy :
  Types.db_id -> Types.cfhandle_id -> Rocks_types.status_t
  = "rocksdb_cfhandle_destroy"
external rocksdb_db_destroy : Types.db_id -> unit = "rocksdb_db_destroy"
external rocksdb_dboptions_id_set_create_if_missing :
  Types.dboptions_id -> bool -> unit
  = "rocksdb_dboptions_id_set_create_if_missing"
external rocksdb_dboptions_id_get_create_if_missing :
  Types.dboptions_id -> bool = "rocksdb_dboptions_id_get_create_if_missing"
external rocksdb_options_id_set_create_if_missing :
  Types.options_id -> bool -> unit
  = "rocksdb_options_id_set_create_if_missing"
external rocksdb_options_id_get_create_if_missing : Types.options_id -> bool
  = "rocksdb_options_id_get_create_if_missing"
external rocksdb_iterator_create :
  Types.db_id -> Types.roptions_id -> Types.iterator_id
  = "rocksdb_iterator_create"
external rocksdb_iterator_cf_create :
  Types.db_id -> Types.roptions_id -> Types.cfhandle_id -> Types.iterator_id
  = "rocksdb_iterator_cf_create"
external rocksdb_iterator_destroy : Types.iterator_id -> unit
  = "rocksdb_iterator_destroy"
external rocksdb_iter_valid : Types.iterator_id -> bool
  = "rocksdb_iter_valid"
external rocksdb_iter_seek_to_first : Types.iterator_id -> unit
  = "rocksdb_iter_seek_to_first"
external rocksdb_iter_seek_to_last : Types.iterator_id -> unit
  = "rocksdb_iter_seek_to_last"
external rocksdb_iter_seek : Types.iterator_id -> string -> unit
  = "rocksdb_iter_seek"
external rocksdb_iter_seek_for_prev : Types.iterator_id -> string -> unit
  = "rocksdb_iter_seek_for_prev"
external rocksdb_iter_next : Types.iterator_id -> unit = "rocksdb_iter_next"
external rocksdb_iter_prev : Types.iterator_id -> unit = "rocksdb_iter_prev"
external rocksdb_iter_key : Types.iterator_id -> string = "rocksdb_iter_key"
external rocksdb_iter_value : Types.iterator_id -> string
  = "rocksdb_iter_value"
external rocksdb_iter_status : Types.iterator_id -> Rocks_types.status_t
  = "rocksdb_iter_status"
external rocksdb_writebatch_create : unit -> Types.writebatch_id
  = "rocksdb_writebatch_create"
external rocksdb_writebatch_destroy : Types.writebatch_id -> unit
  = "rocksdb_writebatch_destroy"
external rocksdb_writebatch_put :
  Types.writebatch_id -> string -> string -> unit = "rocksdb_writebatch_put"
external rocksdb_writebatch_cf_put :
  Types.writebatch_id -> Types.cfhandle_id -> string -> string -> unit
  = "rocksdb_writebatch_cf_put"
external rocksdb_writebatch_delete : Types.writebatch_id -> string -> unit
  = "rocksdb_writebatch_delete"
external rocksdb_writebatch_cf_delete :
  Types.writebatch_id -> Types.cfhandle_id -> string -> unit
  = "rocksdb_writebatch_cf_delete"
external rocksdb_writebatch_delete_range :
  Types.writebatch_id -> string -> string -> unit
  = "rocksdb_writebatch_delete_range"
external rocksdb_writebatch_cf_delete_range :
  Types.writebatch_id -> Types.cfhandle_id -> string -> string -> unit
  = "rocksdb_writebatch_cf_delete_range"
external rocksdb_writebatch_single_delete :
  Types.writebatch_id -> string -> unit = "rocksdb_writebatch_single_delete"
external rocksdb_writebatch_cf_single_delete :
  Types.writebatch_id -> Types.cfhandle_id -> string -> unit
  = "rocksdb_writebatch_cf_single_delete"
external rocksdb_write :
  Types.db_id ->
  Types.woptions_id -> Types.writebatch_id -> Rocks_types.status_t
  = "rocksdb_write"
external rocksdb_get :
  Types.db_id -> Types.roptions_id -> string -> Rocks_types.status_t * string
  = "rocksdb_get"
external rocksdb_cf_get :
  Types.db_id ->
  Types.roptions_id ->
  Types.cfhandle_id -> string -> Rocks_types.status_t * string
  = "rocksdb_cf_get"
external rocksdb_put :
  Types.db_id ->
  Types.woptions_id -> string -> string -> Rocks_types.status_t
  = "rocksdb_put"
external rocksdb_cf_put :
  Types.db_id ->
  Types.woptions_id ->
  Types.cfhandle_id -> string -> string -> Rocks_types.status_t
  = "rocksdb_cf_put"
external rocksdb_delete :
  Types.db_id -> Types.woptions_id -> string -> Rocks_types.status_t
  = "rocksdb_delete"
external rocksdb_cf_delete :
  Types.db_id ->
  Types.woptions_id -> Types.cfhandle_id -> string -> Rocks_types.status_t
  = "rocksdb_cf_delete"
external rocksdb_export_dboptions : Types.dboptions_id -> DBOptionsST.t
  = "rocksdb_export_dboptions"
