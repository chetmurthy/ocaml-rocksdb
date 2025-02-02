
#include <stddef.h>
#include <string.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/custom.h>
#include <caml/bigarray.h>

#include <stdio.h>
#include <string>
#include <unistd.h>
#include <ostream>
#include <iostream>
#include <vector>

#include "rocksdb/comparator.h"
#include "rocksdb/db.h"
#include "rocksdb/iterator.h"
#include "rocksdb/write_batch.h"
#include "ocaml_rocksdb.inc"
#include "cppffi.h"

#ifndef dboptions_t_DEFINED
#define dboptions_t_DEFINED
struct dboptions_t {
  bool create_if_missing ;
  bool create_missing_column_families ;
  bool error_if_exists ;
  bool paranoid_checks ;
  unsigned char info_log_level ;
  int max_open_files ;
  int max_file_opening_threads ;
  uint64_t max_total_wal_size ;
  bool use_fsync ;
  std::string db_log_dir ;
  std::string wal_dir ;
  uint64_t delete_obsolete_files_period_micros ;
  int max_background_jobs ;
  int max_background_compactions ;
  uint32_t max_subcompactions ;
  int max_background_flushes ;
  size_t max_log_file_size ;
  size_t log_file_time_to_roll ;
  size_t keep_log_file_num ;
  size_t recycle_log_file_num ;
  uint64_t max_manifest_file_size ;
  int table_cache_numshardbits ;
  uint64_t _WAL_ttl_seconds ;
  uint64_t _WAL_size_limit_MB ;
  size_t manifest_preallocation_size ;
  bool allow_mmap_reads ;
  bool allow_mmap_writes ;
  bool use_direct_reads ;
  bool use_direct_io_for_flush_and_compaction ;
  bool allow_fallocate ;
  bool is_fd_close_on_exec ;
  unsigned int stats_dump_period_sec ;
  bool advise_random_on_open ;
  size_t db_write_buffer_size ;
  size_t compaction_readahead_size ;
  size_t random_access_max_buffer_size ;
  size_t writable_file_max_buffer_size ;
  bool use_adaptive_mutex ;
  uint64_t bytes_per_sync ;
  uint64_t wal_bytes_per_sync ;
  bool enable_thread_tracking ;
  uint64_t delayed_write_rate ;
  bool enable_pipelined_write ;
  bool allow_concurrent_memtable_write ;
  bool enable_write_thread_adaptive_yield ;
  uint64_t write_thread_max_yield_usec ;
  uint64_t write_thread_slow_yield_usec ;
  bool skip_stats_update_on_db_open ;
  char wal_recovery_mode ;
  bool allow_2pc ;
  bool fail_if_options_file_error ;
  bool dump_malloc_stats ;
  bool avoid_flush_during_recovery ;
  bool avoid_flush_during_shutdown ;
  bool allow_ingest_behind ;
  bool manual_wal_flush ;
} ;
#endif
typedef size_t size_t;
typedef rocksdb::WALRecoveryMode wal_recovery_mode_t;
value c2ml(const wal_recovery_mode_t& _cvalue);
void ml2c(const value _mlvalue, wal_recovery_mode_t *_cvaluep);
typedef rocksdb::Status status;
typedef rocksdb::ColumnFamilyHandle* cfhandle_id;
value c2ml(const cfhandle_id& _cvalue);
void ml2c(const value _mlvalue, cfhandle_id *_cvaluep);
typedef rocksdb::DB* db_id;
value c2ml(const db_id& _cvalue);
void ml2c(const value _mlvalue, db_id *_cvaluep);
typedef Opt< rocksdb::DB >* db_id_opt;
value c2ml(const Opt< rocksdb::DB >& _cvalue);
typedef rocksdb::Options* options_id;
value c2ml(const options_id& _cvalue);
void ml2c(const value _mlvalue, options_id *_cvaluep);
typedef rocksdb::DBOptions* dboptions_id;
value c2ml(const dboptions_id& _cvalue);
void ml2c(const value _mlvalue, dboptions_id *_cvaluep);
typedef rocksdb::ColumnFamilyOptions* cfoptions_id;
value c2ml(const cfoptions_id& _cvalue);
void ml2c(const value _mlvalue, cfoptions_id *_cvaluep);
typedef rocksdb::ReadOptions* roptions_id;
value c2ml(const roptions_id& _cvalue);
void ml2c(const value _mlvalue, roptions_id *_cvaluep);
typedef rocksdb::WriteOptions* woptions_id;
value c2ml(const woptions_id& _cvalue);
void ml2c(const value _mlvalue, woptions_id *_cvaluep);
typedef rocksdb::Comparator* comparator_id;
value c2ml(const comparator_id& _cvalue);
void ml2c(const value _mlvalue, comparator_id *_cvaluep);
typedef rocksdb::ColumnFamilyDescriptor cfd;
void ml2c(const value _mlvalue, cfd *_cvaluep);
value c2ml(const Opt< char >& _cvalue);
value c2ml(const rocksdb::Status& _cvalue);
typedef rocksdb::Iterator* iterator_id;
value c2ml(const iterator_id& _cvalue);
void ml2c(const value _mlvalue, iterator_id *_cvaluep);
typedef rocksdb::WriteBatch* writebatch_id;
value c2ml(const writebatch_id& _cvalue);
void ml2c(const value _mlvalue, writebatch_id *_cvaluep);
typedef struct dboptions_t dboptions;
void ml2c(const value _mlvalue, dboptions *_cvaluep);
value c2ml(const dboptions& _cvalue);

#include "cppffi.inc"





value c2ml(const wal_recovery_mode_t& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml(static_cast<int>(_cvalue)); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, wal_recovery_mode_t *_cvaluep) {
  { char xx ; ml2c(_mlvalue, &xx); *_cvaluep = static_cast<rocksdb::WALRecoveryMode>(xx) ; } ;
}



value c2ml(const cfhandle_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, cfhandle_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


value c2ml(const db_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, db_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


value c2ml(const Opt< rocksdb::DB >& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  
  assert(NULL != _cvalue.it) ;
  _mlvalue = c2ml(_cvalue.it) ;
 ;
  CAMLreturn(_mlvalue);
}


value c2ml(const options_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, options_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


value c2ml(const dboptions_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, dboptions_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


value c2ml(const cfoptions_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, cfoptions_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


value c2ml(const roptions_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, roptions_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


value c2ml(const woptions_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, woptions_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


value c2ml(const comparator_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, comparator_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}


void ml2c(const value _mlvalue, cfd *_cvaluep) {
  
  std::tuple<std::string, cfoptions_id> tmp;
  ml2c(_mlvalue, &tmp) ;
  *_cvaluep = rocksdb::ColumnFamilyDescriptor(std::get<0>(tmp), *(std::get<1>(tmp))) ;
 ;
}


std::string demarsh_state(const char *state) {
  assert(NULL != state) ;
  uint32_t size;
  memcpy(&size, state, sizeof(size));
  const char* body = &(state[4]);
  return std::string(body, size) ;
}

value c2ml(const Opt< char >& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  assert(NULL != _cvalue.it) ;
  _mlvalue = c2ml(demarsh_state(_cvalue.it)) ; ;
  CAMLreturn(_mlvalue);
}

value c2ml(const rocksdb::Status& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  std::string state = _cvalue.ToString() ;
  _mlvalue = c2ml(_cvalue.code(), _cvalue.subcode(), state) ; ;
  CAMLreturn(_mlvalue);
}

extern "C" value rocksdb_cfoptions_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  cfoptions_id _res0;
  /* BODY */
  _res0 = new rocksdb::ColumnFamilyOptions() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_cfoptions_destroy(value _mlv_opth) {
  CAMLparam1(_mlv_opth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  cfoptions_id opth;
  ml2c(_mlv_opth, &opth);
  
  /* BODY */
  if (NULL != opth) {
    delete opth ;
    ml2c_set_owned_pointer<cfoptions_id>(_mlv_opth, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_roptions_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  roptions_id _res0;
  /* BODY */
  _res0 = new rocksdb::ReadOptions() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_roptions_destroy(value _mlv_opth) {
  CAMLparam1(_mlv_opth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  roptions_id opth;
  ml2c(_mlv_opth, &opth);
  
  /* BODY */
  if (NULL != opth) {
    delete opth ;
    ml2c_set_owned_pointer<roptions_id>(_mlv_opth, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_woptions_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  woptions_id _res0;
  /* BODY */
  _res0 = new rocksdb::WriteOptions() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_woptions_destroy(value _mlv_opth) {
  CAMLparam1(_mlv_opth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  woptions_id opth;
  ml2c(_mlv_opth, &opth);
  
  /* BODY */
  if (NULL != opth) {
    delete opth ;
    ml2c_set_owned_pointer<woptions_id>(_mlv_opth, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_dboptions_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  dboptions_id _res0;
  /* BODY */
  _res0 = new rocksdb::DBOptions() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_dboptions_destroy(value _mlv_opth) {
  CAMLparam1(_mlv_opth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  dboptions_id opth;
  ml2c(_mlv_opth, &opth);
  
  /* BODY */
  if (NULL != opth) {
    delete opth ;
    ml2c_set_owned_pointer<dboptions_id>(_mlv_opth, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_list_column_families(value _mlv_opth, value _mlv_name) {
  CAMLparam2(_mlv_opth, _mlv_name);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  dboptions_id opth;
  ml2c(_mlv_opth, &opth);
  std::string name;
  ml2c(_mlv_name, &name);
  status _res0;
  std::vector< std::string > _res1;
  /* BODY */
  _res0 = rocksdb::DB::ListColumnFamilies(*opth, name, &_res1);
  if (!_res0.ok()) _res1.clear() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_bytewise_comparator_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  comparator_id _res0;
  /* BODY */
  _res0 = const_cast<rocksdb::Comparator *>(rocksdb::BytewiseComparator());
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_reverse_bytewise_comparator_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  comparator_id _res0;
  /* BODY */
  _res0 = const_cast<rocksdb::Comparator *>(rocksdb::ReverseBytewiseComparator());
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_myrocks_comparator_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  comparator_id _res0;
  /* BODY */
  _res0 = new myrocks::Rdb_pk_comparator() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_rev_myrocks_comparator_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  comparator_id _res0;
  /* BODY */
  _res0 = new myrocks::Rdb_rev_comparator() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_cfoptions_set_comparator(value _mlv_opth, value _mlv_cmp) {
  CAMLparam2(_mlv_opth, _mlv_cmp);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  cfoptions_id opth;
  ml2c(_mlv_opth, &opth);
  comparator_id cmp;
  ml2c(_mlv_cmp, &cmp);
  
  /* BODY */
  opth->comparator = cmp;
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_options_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  options_id _res0;
  /* BODY */
  _res0 = new rocksdb::Options() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_options_destroy(value _mlv_opth) {
  CAMLparam1(_mlv_opth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  options_id opth;
  ml2c(_mlv_opth, &opth);
  
  /* BODY */
  if (NULL != opth) {
    delete opth ;
    ml2c_set_owned_pointer<options_id>(_mlv_opth, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_open(value _mlv_opth, value _mlv_name) {
  CAMLparam2(_mlv_opth, _mlv_name);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  options_id opth;
  ml2c(_mlv_opth, &opth);
  std::string name;
  ml2c(_mlv_name, &name);
  status _res0;
  db_id_opt _res1;
  /* BODY */
  rocksdb::DB *out_dbptr = NULL;
  _res0 = rocksdb::DB::Open(*opth, name, &out_dbptr);
  if (!_res0.ok()) { out_dbptr = NULL ; }
  OptWrap<rocksdb::DB> w(out_dbptr);
  _res1 = w.p();

  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_open_column_families(value _mlv_opth, value _mlv_name, value _mlv_cfds) {
  CAMLparam3(_mlv_opth, _mlv_name, _mlv_cfds);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  dboptions_id opth;
  ml2c(_mlv_opth, &opth);
  std::string name;
  ml2c(_mlv_name, &name);
  std::vector< cfd > cfds;
  ml2c(_mlv_cfds, &cfds);
  status _res0;
  std::vector< cfhandle_id > _res1;
  db_id_opt _res2;
  /* BODY */
  rocksdb::DB *out_dbptr = NULL;
  _res0 = rocksdb::DB::Open(*opth, name, cfds, &_res1, &out_dbptr);
  if (!_res0.ok()) { _res1.clear() ; out_dbptr = NULL ; }
  OptWrap<rocksdb::DB> w(out_dbptr);
  _res2 = w.p();

  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1, _res2);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_open_for_readonly(value _mlv_opth, value _mlv_name, value _mlv_error_if_log_file_exist) {
  CAMLparam3(_mlv_opth, _mlv_name, _mlv_error_if_log_file_exist);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  options_id opth;
  ml2c(_mlv_opth, &opth);
  std::string name;
  ml2c(_mlv_name, &name);
  bool error_if_log_file_exist;
  ml2c(_mlv_error_if_log_file_exist, &error_if_log_file_exist);
  status _res0;
  db_id_opt _res1;
  /* BODY */
  rocksdb::DB *out_dbptr = NULL;
  _res0 = rocksdb::DB::OpenForReadOnly(*opth, name, &out_dbptr, error_if_log_file_exist);
  if (!_res0.ok()) { out_dbptr = NULL ; }
  OptWrap<rocksdb::DB> w(out_dbptr);
  _res1 = w.p();

  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_open_column_families_for_readonly(value _mlv_opth, value _mlv_name, value _mlv_cfds, value _mlv_error_if_log_file_exist) {
  CAMLparam4(_mlv_opth, _mlv_name, _mlv_cfds, _mlv_error_if_log_file_exist);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  dboptions_id opth;
  ml2c(_mlv_opth, &opth);
  std::string name;
  ml2c(_mlv_name, &name);
  std::vector< cfd > cfds;
  ml2c(_mlv_cfds, &cfds);
  bool error_if_log_file_exist;
  ml2c(_mlv_error_if_log_file_exist, &error_if_log_file_exist);
  status _res0;
  std::vector< cfhandle_id > _res1;
  db_id_opt _res2;
  /* BODY */
  rocksdb::DB *out_dbptr = NULL;
  _res0 = rocksdb::DB::OpenForReadOnly(*opth, name, cfds, &_res1, &out_dbptr, error_if_log_file_exist);
  if (!_res0.ok()) { _res1.clear() ; out_dbptr = NULL ; }
  OptWrap<rocksdb::DB> w(out_dbptr);
  _res2 = w.p();

  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1, _res2);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_create_column_family(value _mlv_dbh, value _mlv_opth, value _mlv_name) {
  CAMLparam3(_mlv_dbh, _mlv_opth, _mlv_name);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  cfoptions_id opth;
  ml2c(_mlv_opth, &opth);
  std::string name;
  ml2c(_mlv_name, &name);
  status _res0;
  cfhandle_id _res1;
  /* BODY */
  
  _res0 = dbh->CreateColumnFamily(*opth, name, &_res1);
  if (!_res0.ok()) { _res1 = NULL ; }

  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_drop_column_family(value _mlv_dbh, value _mlv_cfh) {
  CAMLparam2(_mlv_dbh, _mlv_cfh);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  status _res0;
  /* BODY */
  
  _res0 = dbh->DropColumnFamily(cfh);

  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_cfhandle_destroy(value _mlv_dbh, value _mlv_cfh) {
  CAMLparam2(_mlv_dbh, _mlv_cfh);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  status _res0;
  /* BODY */
  _res0 = dbh->DestroyColumnFamilyHandle(cfh);
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_db_destroy(value _mlv_dbh) {
  CAMLparam1(_mlv_dbh);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  
  /* BODY */
  if (NULL != dbh) {
    delete dbh ;
    ml2c_set_owned_pointer<db_id>(_mlv_dbh, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_dboptions_id_set_create_if_missing(value _mlv_rcvr, value _mlv_create_if_missing) {
  CAMLparam2(_mlv_rcvr, _mlv_create_if_missing);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  dboptions_id rcvr;
  ml2c(_mlv_rcvr, &rcvr);
  bool create_if_missing;
  ml2c(_mlv_create_if_missing, &create_if_missing);
  
  /* BODY */
  rcvr->create_if_missing = create_if_missing;
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_dboptions_id_get_create_if_missing(value _mlv_rcvr) {
  CAMLparam1(_mlv_rcvr);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  dboptions_id rcvr;
  ml2c(_mlv_rcvr, &rcvr);
  bool _res0;
  /* BODY */
  _res0 = rcvr->create_if_missing;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_options_id_set_create_if_missing(value _mlv_rcvr, value _mlv_create_if_missing) {
  CAMLparam2(_mlv_rcvr, _mlv_create_if_missing);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  options_id rcvr;
  ml2c(_mlv_rcvr, &rcvr);
  bool create_if_missing;
  ml2c(_mlv_create_if_missing, &create_if_missing);
  
  /* BODY */
  rcvr->create_if_missing = create_if_missing;
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_options_id_get_create_if_missing(value _mlv_rcvr) {
  CAMLparam1(_mlv_rcvr);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  options_id rcvr;
  ml2c(_mlv_rcvr, &rcvr);
  bool _res0;
  /* BODY */
  _res0 = rcvr->create_if_missing;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}


value c2ml(const iterator_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, iterator_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}

extern "C" value rocksdb_iterator_create(value _mlv_dbh, value _mlv_ropth) {
  CAMLparam2(_mlv_dbh, _mlv_ropth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  roptions_id ropth;
  ml2c(_mlv_ropth, &ropth);
  iterator_id _res0;
  /* BODY */
  _res0 = dbh->NewIterator(*ropth) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iterator_cf_create(value _mlv_dbh, value _mlv_ropth, value _mlv_cfh) {
  CAMLparam3(_mlv_dbh, _mlv_ropth, _mlv_cfh);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  roptions_id ropth;
  ml2c(_mlv_ropth, &ropth);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  iterator_id _res0;
  /* BODY */
  _res0 = dbh->NewIterator(*ropth, cfh) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iterator_destroy(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  
  /* BODY */
  if (NULL != ith) {
    delete ith ;
    ml2c_set_owned_pointer<iterator_id>(_mlv_ith, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_valid(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  bool _res0;
  /* BODY */
  _res0 = ith->Valid();
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_seek_to_first(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  
  /* BODY */
  ith->SeekToFirst();
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_seek_to_last(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  
  /* BODY */
  ith->SeekToLast();
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_seek(value _mlv_ith, value _mlv_target) {
  CAMLparam2(_mlv_ith, _mlv_target);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  std::string target;
  ml2c(_mlv_target, &target);
  
  /* BODY */
  ith->Seek(target);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_seek_for_prev(value _mlv_ith, value _mlv_target) {
  CAMLparam2(_mlv_ith, _mlv_target);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  std::string target;
  ml2c(_mlv_target, &target);
  
  /* BODY */
  ith->SeekForPrev(target);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_next(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  
  /* BODY */
  ith->Next();
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_prev(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  
  /* BODY */
  ith->Prev();
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_key(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  std::string _res0;
  /* BODY */
  _res0 = ith->key().ToString();
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_value(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  std::string _res0;
  /* BODY */
  _res0 = ith->value().ToString();
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_iter_status(value _mlv_ith) {
  CAMLparam1(_mlv_ith);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  iterator_id ith;
  ml2c(_mlv_ith, &ith);
  status _res0;
  /* BODY */
  _res0 = ith->status();
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}


value c2ml(const writebatch_id& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  _mlvalue = c2ml_owned_pointer(_cvalue); ;
  CAMLreturn(_mlvalue);
}

void ml2c(const value _mlvalue, writebatch_id *_cvaluep) {
  ml2c_owned_pointer(_mlvalue, _cvaluep); ;
}

extern "C" value rocksdb_writebatch_create() {
  CAMLparam0();
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  
  writebatch_id _res0;
  /* BODY */
  _res0 = new rocksdb::WriteBatch() ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_destroy(value _mlv_opth) {
  CAMLparam1(_mlv_opth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id opth;
  ml2c(_mlv_opth, &opth);
  
  /* BODY */
  if (NULL != opth) {
    delete opth ;
    ml2c_set_owned_pointer<writebatch_id>(_mlv_opth, NULL);
  }

  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_put(value _mlv_wbh, value _mlv_key, value _mlv_values) {
  CAMLparam3(_mlv_wbh, _mlv_key, _mlv_values);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  std::string key;
  ml2c(_mlv_key, &key);
  std::string values;
  ml2c(_mlv_values, &values);
  
  /* BODY */
  wbh->Put(key, values);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_cf_put(value _mlv_wbh, value _mlv_cfh, value _mlv_key, value _mlv_values) {
  CAMLparam4(_mlv_wbh, _mlv_cfh, _mlv_key, _mlv_values);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  std::string key;
  ml2c(_mlv_key, &key);
  std::string values;
  ml2c(_mlv_values, &values);
  
  /* BODY */
  wbh->Put(cfh, key, values);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_delete(value _mlv_wbh, value _mlv_key) {
  CAMLparam2(_mlv_wbh, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  std::string key;
  ml2c(_mlv_key, &key);
  
  /* BODY */
  wbh->Delete(key);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_cf_delete(value _mlv_wbh, value _mlv_cfh, value _mlv_key) {
  CAMLparam3(_mlv_wbh, _mlv_cfh, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  std::string key;
  ml2c(_mlv_key, &key);
  
  /* BODY */
  wbh->Delete(cfh, key);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_delete_range(value _mlv_wbh, value _mlv_bkey, value _mlv_ekey) {
  CAMLparam3(_mlv_wbh, _mlv_bkey, _mlv_ekey);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  std::string bkey;
  ml2c(_mlv_bkey, &bkey);
  std::string ekey;
  ml2c(_mlv_ekey, &ekey);
  
  /* BODY */
  wbh->DeleteRange(bkey, ekey);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_cf_delete_range(value _mlv_wbh, value _mlv_cfh, value _mlv_bkey, value _mlv_ekey) {
  CAMLparam4(_mlv_wbh, _mlv_cfh, _mlv_bkey, _mlv_ekey);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  std::string bkey;
  ml2c(_mlv_bkey, &bkey);
  std::string ekey;
  ml2c(_mlv_ekey, &ekey);
  
  /* BODY */
  wbh->DeleteRange(cfh, bkey, ekey);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_single_delete(value _mlv_wbh, value _mlv_key) {
  CAMLparam2(_mlv_wbh, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  std::string key;
  ml2c(_mlv_key, &key);
  
  /* BODY */
  wbh->SingleDelete(key);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_writebatch_cf_single_delete(value _mlv_wbh, value _mlv_cfh, value _mlv_key) {
  CAMLparam3(_mlv_wbh, _mlv_cfh, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  std::string key;
  ml2c(_mlv_key, &key);
  
  /* BODY */
  wbh->SingleDelete(cfh, key);
  /* C->ML*/
  
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_write(value _mlv_dbh, value _mlv_opth, value _mlv_wbh) {
  CAMLparam3(_mlv_dbh, _mlv_opth, _mlv_wbh);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  woptions_id opth;
  ml2c(_mlv_opth, &opth);
  writebatch_id wbh;
  ml2c(_mlv_wbh, &wbh);
  status _res0;
  /* BODY */
  _res0 = dbh->Write(*opth, wbh) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_get(value _mlv_dbh, value _mlv_opth, value _mlv_key) {
  CAMLparam3(_mlv_dbh, _mlv_opth, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  roptions_id opth;
  ml2c(_mlv_opth, &opth);
  std::string key;
  ml2c(_mlv_key, &key);
  status _res0;
  std::string _res1;
  /* BODY */
  _res0 = dbh->Get(*opth, key, &_res1) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_cf_get(value _mlv_dbh, value _mlv_opth, value _mlv_cfh, value _mlv_key) {
  CAMLparam4(_mlv_dbh, _mlv_opth, _mlv_cfh, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  roptions_id opth;
  ml2c(_mlv_opth, &opth);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  std::string key;
  ml2c(_mlv_key, &key);
  status _res0;
  std::string _res1;
  /* BODY */
  _res0 = dbh->Get(*opth, cfh, key, &_res1) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0, _res1);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_put(value _mlv_dbh, value _mlv_opth, value _mlv_key, value _mlv_val) {
  CAMLparam4(_mlv_dbh, _mlv_opth, _mlv_key, _mlv_val);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  woptions_id opth;
  ml2c(_mlv_opth, &opth);
  std::string key;
  ml2c(_mlv_key, &key);
  std::string val;
  ml2c(_mlv_val, &val);
  status _res0;
  /* BODY */
  _res0 = dbh->Put(*opth, key, val) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_cf_put(value _mlv_dbh, value _mlv_opth, value _mlv_cfh, value _mlv_key, value _mlv_val) {
  CAMLparam5(_mlv_dbh, _mlv_opth, _mlv_cfh, _mlv_key, _mlv_val);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  woptions_id opth;
  ml2c(_mlv_opth, &opth);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  std::string key;
  ml2c(_mlv_key, &key);
  std::string val;
  ml2c(_mlv_val, &val);
  status _res0;
  /* BODY */
  _res0 = dbh->Put(*opth, cfh, key, val) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_delete(value _mlv_dbh, value _mlv_opth, value _mlv_key) {
  CAMLparam3(_mlv_dbh, _mlv_opth, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  woptions_id opth;
  ml2c(_mlv_opth, &opth);
  std::string key;
  ml2c(_mlv_key, &key);
  status _res0;
  /* BODY */
  _res0 = dbh->Delete(*opth, key) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

extern "C" value rocksdb_cf_delete(value _mlv_dbh, value _mlv_opth, value _mlv_cfh, value _mlv_key) {
  CAMLparam4(_mlv_dbh, _mlv_opth, _mlv_cfh, _mlv_key);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  db_id dbh;
  ml2c(_mlv_dbh, &dbh);
  woptions_id opth;
  ml2c(_mlv_opth, &opth);
  cfhandle_id cfh;
  ml2c(_mlv_cfh, &cfh);
  std::string key;
  ml2c(_mlv_key, &key);
  status _res0;
  /* BODY */
  _res0 = dbh->Delete(*opth, cfh, key) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}





void ml2c(const value _mlvalue, dboptions *_cvaluep) {
  ml2c(Field(_mlvalue,0), &(_cvaluep->create_if_missing));
  ml2c(Field(_mlvalue,1), &(_cvaluep->create_missing_column_families));
  ml2c(Field(_mlvalue,2), &(_cvaluep->error_if_exists));
  ml2c(Field(_mlvalue,3), &(_cvaluep->paranoid_checks));
  ml2c(Field(_mlvalue,4), &(_cvaluep->info_log_level));
  ml2c(Field(_mlvalue,5), &(_cvaluep->max_open_files));
  ml2c(Field(_mlvalue,6), &(_cvaluep->max_file_opening_threads));
  ml2c(Field(_mlvalue,7), &(_cvaluep->max_total_wal_size));
  ml2c(Field(_mlvalue,8), &(_cvaluep->use_fsync));
  ml2c(Field(_mlvalue,9), &(_cvaluep->db_log_dir));
  ml2c(Field(_mlvalue,10), &(_cvaluep->wal_dir));
  ml2c(Field(_mlvalue,11), &(_cvaluep->delete_obsolete_files_period_micros));
  ml2c(Field(_mlvalue,12), &(_cvaluep->max_background_jobs));
  ml2c(Field(_mlvalue,13), &(_cvaluep->max_background_compactions));
  ml2c(Field(_mlvalue,14), &(_cvaluep->max_subcompactions));
  ml2c(Field(_mlvalue,15), &(_cvaluep->max_background_flushes));
  ml2c(Field(_mlvalue,16), &(_cvaluep->max_log_file_size));
  ml2c(Field(_mlvalue,17), &(_cvaluep->log_file_time_to_roll));
  ml2c(Field(_mlvalue,18), &(_cvaluep->keep_log_file_num));
  ml2c(Field(_mlvalue,19), &(_cvaluep->recycle_log_file_num));
  ml2c(Field(_mlvalue,20), &(_cvaluep->max_manifest_file_size));
  ml2c(Field(_mlvalue,21), &(_cvaluep->table_cache_numshardbits));
  ml2c(Field(_mlvalue,22), &(_cvaluep->_WAL_ttl_seconds));
  ml2c(Field(_mlvalue,23), &(_cvaluep->_WAL_size_limit_MB));
  ml2c(Field(_mlvalue,24), &(_cvaluep->manifest_preallocation_size));
  ml2c(Field(_mlvalue,25), &(_cvaluep->allow_mmap_reads));
  ml2c(Field(_mlvalue,26), &(_cvaluep->allow_mmap_writes));
  ml2c(Field(_mlvalue,27), &(_cvaluep->use_direct_reads));
  ml2c(Field(_mlvalue,28), &(_cvaluep->use_direct_io_for_flush_and_compaction));
  ml2c(Field(_mlvalue,29), &(_cvaluep->allow_fallocate));
  ml2c(Field(_mlvalue,30), &(_cvaluep->is_fd_close_on_exec));
  ml2c(Field(_mlvalue,31), &(_cvaluep->stats_dump_period_sec));
  ml2c(Field(_mlvalue,32), &(_cvaluep->advise_random_on_open));
  ml2c(Field(_mlvalue,33), &(_cvaluep->db_write_buffer_size));
  ml2c(Field(_mlvalue,34), &(_cvaluep->compaction_readahead_size));
  ml2c(Field(_mlvalue,35), &(_cvaluep->random_access_max_buffer_size));
  ml2c(Field(_mlvalue,36), &(_cvaluep->writable_file_max_buffer_size));
  ml2c(Field(_mlvalue,37), &(_cvaluep->use_adaptive_mutex));
  ml2c(Field(_mlvalue,38), &(_cvaluep->bytes_per_sync));
  ml2c(Field(_mlvalue,39), &(_cvaluep->wal_bytes_per_sync));
  ml2c(Field(_mlvalue,40), &(_cvaluep->enable_thread_tracking));
  ml2c(Field(_mlvalue,41), &(_cvaluep->delayed_write_rate));
  ml2c(Field(_mlvalue,42), &(_cvaluep->enable_pipelined_write));
  ml2c(Field(_mlvalue,43), &(_cvaluep->allow_concurrent_memtable_write));
  ml2c(Field(_mlvalue,44), &(_cvaluep->enable_write_thread_adaptive_yield));
  ml2c(Field(_mlvalue,45), &(_cvaluep->write_thread_max_yield_usec));
  ml2c(Field(_mlvalue,46), &(_cvaluep->write_thread_slow_yield_usec));
  ml2c(Field(_mlvalue,47), &(_cvaluep->skip_stats_update_on_db_open));
  ml2c(Field(_mlvalue,48), &(_cvaluep->wal_recovery_mode));
  ml2c(Field(_mlvalue,49), &(_cvaluep->allow_2pc));
  ml2c(Field(_mlvalue,50), &(_cvaluep->fail_if_options_file_error));
  ml2c(Field(_mlvalue,51), &(_cvaluep->dump_malloc_stats));
  ml2c(Field(_mlvalue,52), &(_cvaluep->avoid_flush_during_recovery));
  ml2c(Field(_mlvalue,53), &(_cvaluep->avoid_flush_during_shutdown));
  ml2c(Field(_mlvalue,54), &(_cvaluep->allow_ingest_behind));
  ml2c(Field(_mlvalue,55), &(_cvaluep->manual_wal_flush)); ;
}

value c2ml(const dboptions& _cvalue) {
  CAMLparam0();
  CAMLlocal1(_mlvalue);
  
  _mlvalue = caml_alloc(56, 0) ;
  Store_field(_mlvalue, 0, c2ml(_cvalue.create_if_missing));
  Store_field(_mlvalue, 1, c2ml(_cvalue.create_missing_column_families));
  Store_field(_mlvalue, 2, c2ml(_cvalue.error_if_exists));
  Store_field(_mlvalue, 3, c2ml(_cvalue.paranoid_checks));
  Store_field(_mlvalue, 4, c2ml(_cvalue.info_log_level));
  Store_field(_mlvalue, 5, c2ml(_cvalue.max_open_files));
  Store_field(_mlvalue, 6, c2ml(_cvalue.max_file_opening_threads));
  Store_field(_mlvalue, 7, c2ml(_cvalue.max_total_wal_size));
  Store_field(_mlvalue, 8, c2ml(_cvalue.use_fsync));
  Store_field(_mlvalue, 9, c2ml(_cvalue.db_log_dir));
  Store_field(_mlvalue, 10, c2ml(_cvalue.wal_dir));
  Store_field(_mlvalue, 11, c2ml(_cvalue.delete_obsolete_files_period_micros));
  Store_field(_mlvalue, 12, c2ml(_cvalue.max_background_jobs));
  Store_field(_mlvalue, 13, c2ml(_cvalue.max_background_compactions));
  Store_field(_mlvalue, 14, c2ml(_cvalue.max_subcompactions));
  Store_field(_mlvalue, 15, c2ml(_cvalue.max_background_flushes));
  Store_field(_mlvalue, 16, c2ml(_cvalue.max_log_file_size));
  Store_field(_mlvalue, 17, c2ml(_cvalue.log_file_time_to_roll));
  Store_field(_mlvalue, 18, c2ml(_cvalue.keep_log_file_num));
  Store_field(_mlvalue, 19, c2ml(_cvalue.recycle_log_file_num));
  Store_field(_mlvalue, 20, c2ml(_cvalue.max_manifest_file_size));
  Store_field(_mlvalue, 21, c2ml(_cvalue.table_cache_numshardbits));
  Store_field(_mlvalue, 22, c2ml(_cvalue._WAL_ttl_seconds));
  Store_field(_mlvalue, 23, c2ml(_cvalue._WAL_size_limit_MB));
  Store_field(_mlvalue, 24, c2ml(_cvalue.manifest_preallocation_size));
  Store_field(_mlvalue, 25, c2ml(_cvalue.allow_mmap_reads));
  Store_field(_mlvalue, 26, c2ml(_cvalue.allow_mmap_writes));
  Store_field(_mlvalue, 27, c2ml(_cvalue.use_direct_reads));
  Store_field(_mlvalue, 28, c2ml(_cvalue.use_direct_io_for_flush_and_compaction));
  Store_field(_mlvalue, 29, c2ml(_cvalue.allow_fallocate));
  Store_field(_mlvalue, 30, c2ml(_cvalue.is_fd_close_on_exec));
  Store_field(_mlvalue, 31, c2ml(_cvalue.stats_dump_period_sec));
  Store_field(_mlvalue, 32, c2ml(_cvalue.advise_random_on_open));
  Store_field(_mlvalue, 33, c2ml(_cvalue.db_write_buffer_size));
  Store_field(_mlvalue, 34, c2ml(_cvalue.compaction_readahead_size));
  Store_field(_mlvalue, 35, c2ml(_cvalue.random_access_max_buffer_size));
  Store_field(_mlvalue, 36, c2ml(_cvalue.writable_file_max_buffer_size));
  Store_field(_mlvalue, 37, c2ml(_cvalue.use_adaptive_mutex));
  Store_field(_mlvalue, 38, c2ml(_cvalue.bytes_per_sync));
  Store_field(_mlvalue, 39, c2ml(_cvalue.wal_bytes_per_sync));
  Store_field(_mlvalue, 40, c2ml(_cvalue.enable_thread_tracking));
  Store_field(_mlvalue, 41, c2ml(_cvalue.delayed_write_rate));
  Store_field(_mlvalue, 42, c2ml(_cvalue.enable_pipelined_write));
  Store_field(_mlvalue, 43, c2ml(_cvalue.allow_concurrent_memtable_write));
  Store_field(_mlvalue, 44, c2ml(_cvalue.enable_write_thread_adaptive_yield));
  Store_field(_mlvalue, 45, c2ml(_cvalue.write_thread_max_yield_usec));
  Store_field(_mlvalue, 46, c2ml(_cvalue.write_thread_slow_yield_usec));
  Store_field(_mlvalue, 47, c2ml(_cvalue.skip_stats_update_on_db_open));
  Store_field(_mlvalue, 48, c2ml(_cvalue.wal_recovery_mode));
  Store_field(_mlvalue, 49, c2ml(_cvalue.allow_2pc));
  Store_field(_mlvalue, 50, c2ml(_cvalue.fail_if_options_file_error));
  Store_field(_mlvalue, 51, c2ml(_cvalue.dump_malloc_stats));
  Store_field(_mlvalue, 52, c2ml(_cvalue.avoid_flush_during_recovery));
  Store_field(_mlvalue, 53, c2ml(_cvalue.avoid_flush_during_shutdown));
  Store_field(_mlvalue, 54, c2ml(_cvalue.allow_ingest_behind));
  Store_field(_mlvalue, 55, c2ml(_cvalue.manual_wal_flush));
 ;
  CAMLreturn(_mlvalue);
}

extern "C" value rocksdb_export_dboptions(value _mlv_opth) {
  CAMLparam1(_mlv_opth);
  CAMLlocal1(_mlv_res) ;
  /* ML->C*/
  dboptions_id opth;
  ml2c(_mlv_opth, &opth);
  dboptions _res0;
  /* BODY */
   _res0 = dboptions_t(*opth) ;
  /* C->ML*/
    _mlv_res = c2ml(_res0);
  CAMLreturn(_mlv_res) ;
}

