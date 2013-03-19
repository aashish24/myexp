import cherrypy
import json
from pymongo import connection

class geowebio:

  @cherrypy.expose
  def collections(self):
    result = {}
    conn = connection.MongoClient()
    for i in conn.database_names():
      db = eval("conn." + i)
      result[i] = db.collection_names()

    return json.dumps(result)
