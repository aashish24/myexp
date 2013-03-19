import os
import cherrypy
import json
from pymongo import connection

current_dir = os.path.dirname(os.path.abspath(__file__))

class geoweb:
  @cherrypy.expose
  def collections(self):
    result = {}
    conn = connection.MongoClient()
    for i in conn.database_names():
      db = eval("conn." + i)
      result[i] = db.collection_names()

    return json.dumps(result)
