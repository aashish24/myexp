
import gridfs
import pymongo

class importdb:
  def importData(self, filename, database, collection='fs'):
    conn = pymongo.Connection()
    db = conn[database]
    gf = gridfs.GridFS(db, collection)
    afile = gf.new_file()
    bfile = open(filename)
    afile.write(bfile.read())
    afile.close()

if __name__ == "__main__":
  import sys
  print sys.argv
  if (len(sys.argv) < 3):
    print "usage: script filename databasename "
    sys.exit(1)

  importdbinst = importdb()
  importdbinst.importData(sys.argv[1], sys.argv[2])




