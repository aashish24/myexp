import os
import cherrypy
import json
from pymongo import connection

current_dir = os.path.dirname(os.path.abspath(__file__))

class geoweb:
  @cherrypy.expose
  def collections(self, *args):
    result = {}
    conn = connection.MongoClient()
    if not args:
      for i in conn.database_names():
        db = conn[i]
        result[i] = db.collection_names()

      return json.dumps(result)

    # Get documents from the collections
      for i in conn.database_names():
        db = conn[i]
        for j in db.collection_names():
          coll = db[j]
          result[j] = coll.find()

      return json.dumps(result)
