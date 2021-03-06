/**
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 */

var testGenerator = testSteps();

function testSteps()
{
  const name = this.window ? window.location.pathname : "Splendid Test";

  let request = mozIndexedDB.open(name, 1);
  request.onerror = errorHandler;
  request.onupgradeneeded = grabEventAndContinueHandler;
  request.onsuccess = unexpectedSuccessHandler;

  let request2 = mozIndexedDB.open(name, 2);
  request2.onerror = errorHandler;
  request2.onupgradeneeded = unexpectedSuccessHandler;

  let event = yield;
  is(event.type, "upgradeneeded", "Expect an upgradeneeded event");
  is(event.target, request, "Event should be fired on the request");
  ok(event.target.result instanceof IDBDatabase, "Expect a database here");

  let db = event.target.result;
  is(db.version, 1, "Database has correct version");

  db.onupgradeneeded = function() {
    ok(false, "our ongoing VERSION_CHANGE transaction should exclude any others!");
  }

  db.createObjectStore("foo");

  try {
    db.transaction("foo");
    ok(false, "Transactions should be disallowed now!");
  } catch (e) {
    ok(e instanceof IDBDatabaseException, "Expect an IDBException");
    is(e.code, IDBDatabaseException.NOT_ALLOWED_ERR, "Expect a NOT_ALLOWED_ERR");
  }

  request.transaction.oncomplete = grabEventAndContinueHandler;

  yield;

  // The database is still not fully open here.
  try {
    db.transaction("foo");
    ok(false, "Transactions should be disallowed now!");
  } catch (e) {
    ok(e instanceof IDBDatabaseException, "Expect an IDBException");
    is(e.code, IDBDatabaseException.NOT_ALLOWED_ERR, "Expect a NOT_ALLOWED_ERR");
  }

  request.onsuccess = grabEventAndContinueHandler;

  yield;

  db.onversionchange = function() {
    ok(true, "next setVersion was unblocked appropriately");
    db.close();
  }

  try {
    db.transaction("foo");
    ok(true, "Transactions should be allowed now!");
  } catch (e) {
    ok(false, "Transactions should be allowed now!");
  }

  request2.onupgradeneeded = null;
  request2.onsuccess = grabEventAndContinueHandler;

  yield;

  finishTest();
  yield;
}
