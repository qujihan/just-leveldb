#include <cassert>

#include "leveldb/c.h"
#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "leveldb/write_batch.h"
#include "utils.h"
#include <iostream>

int main() {
  leveldb::DB *db{nullptr};
  leveldb::Options option;
  option.create_if_missing = true;
  leveldb::Status s;

  //
  // creat
  //
  s = leveldb::DB::Open(option, get_database_path(__FILE_NAME__, true), &db);
  if (!s.ok()) {
    std::cout << s.ToString();
  }

  //
  // put
  //
  std::string put_key = "name";
  std::string put_val = "quhaha";
  s = db->Put(leveldb::WriteOptions(), put_key, put_val);

  //
  // get
  //
  std::string get_key = put_key;
  std::string get_val;
  s = db->Get(leveldb::ReadOptions(), get_key, &get_val);
  if (!s.ok()) {
    std::cout << s.ToString();
    if (get_val != put_val) {
      std::cout << "not get" << put_val << std::endl;
    }
  }

  //
  // write batch
  //
  leveldb::WriteBatch batch;
  for (int i = 0; i < 10; i++) {
    batch.Put("key" + std::to_string(i), "value" + std::to_string(i));
  }
  s = db->Write(leveldb::WriteOptions(), &batch);

  //
  // delete
  //
  db->Delete(leveldb::WriteOptions(), "name");

  //
  // iterator
  //
  leveldb::Iterator *iter{db->NewIterator(leveldb::ReadOptions())};
  iter->SeekToFirst();
  while (iter->Valid()) {
    leveldb::Slice key{iter->key()};
    leveldb::Slice val{iter->value()};
    std::cout << "key: " << key.ToString() << ", value: " << val.ToString()
              << std::endl;
    iter->Next();
  }

  delete iter;
  delete db;
}