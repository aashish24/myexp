import gridfs
import pymongo
import os

class importdb:
  def importData(self, filename, database, collection='fs'):
    conn = pymongo.Connection()
    db = conn[database]
    gf = gridfs.GridFS(db, collection)
    afile = gf.new_file()
    bfile = open(filename)
    afile.write(bfile.read())
    afile.close()

  def importFile(seff, filename, database='documents', collection='files'):
    conn = pymongo.Connection()
    db = conn[database]
    coll = db[collection]
    # Get the prefix of the file
    basename = os.path.basename(filename)
    fileprefix = os.path.splitext(basename)[0]
    insertId = coll.insert({"name":fileprefix, "basename":basename})

if __name__ == "__main__":
  import sys
  print sys.argv
  if (len(sys.argv) < 3):
    print "usage: script filename databasename "
    sys.exit(1)

  importdbinst = importdb()
  importdbinst.importFile(sys.argv[1], sys.argv[2])
