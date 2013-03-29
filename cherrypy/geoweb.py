import os
import cherrypy
import json
from pymongo import connection

current_dir = os.path.dirname(os.path.abspath(__file__))

class geoweb:
  @cherrypy.expose
  def mongo(self, *args, **kwargs):
    import mongo
    return mongo.run(args, kwargs)

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
        di["_id"] = str(di["_id"])
      result["data"] =  items
      return json.dumps(result)
    else:
      return json.dumps(result)

  @cherrypy.expose
  def documents(self):
    result = {}
    conn = connection.MongoClient()
    db = conn["documents"]
    for coll in db.collection_names():
      if (coll != "system.indexes"):
        collItems = list(db[coll].find())
        for item in collItems:
          if "_id" in item:
            item["_id"] = str(item["_id"])
        result[coll] = collItems
    return json.dumps(result)
