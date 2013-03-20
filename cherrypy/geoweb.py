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
    db = conn[args[0]]
    coll = db[args[1]]
    if coll is not None:
      items = list(coll.find().limit(20))
      for di in items:
        del di["_id"]
      result["data"] =  items
      return json.dumps(result)
    else:
      return json.dumps(result)
