from flask import Flask, request, session, g, redirect, url_for, abort, \
    render_template, flash
import os
import sqlite3
# from wtforms import Form, BooleanField, StringField, PasswordField, validators

app = Flask(__name__)
app.config.from_object(__name__)
app.config.update(dict(
    DATABASE=os.path.join(app.root_path, 'mliot.db'),
    SECRET_KEY='sudo',
))

app.config.from_envvar('MLIOT_SETTINGS', silent=True)


def connectDatabase(db_path):
    """
    Connects to the application database.
    """
    rv = sqlite3.connect(db_path)
    rv.row_factory = sqlite3.Row 
    return rv


def getDatabase(db_path):
    """
    Opens a new database connection if one is not open yet from the application globals.
    """
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connectDatabase(db_path)
    return g.sqlite_db


@app.teardown_appcontext
def closeDatabase(error):
    """
    Closes the database again at the end of the request.
    """
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()


def initializeDatabase():
    db = getDatabase(app.config['DATABASE'])
    with app.open_resource('schema.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()


@app.cli.command('initdb')
def initdb_handler():
    """
    Make a call to initialize the database.
    """
    initializeDatabase()
    print("Initialized the " + __name__ + " database.")


@app.route('/')
def news_feed():
    # get the database
    # db = getDatabase(app.config['DATABASE'])
    # run the sql command to get the status updates
    # posts = cur.fetchall()
    # return render_template('newsfeed.html', posts=posts)
    return "Hello World!"


@app.route('/profile')
def user_profile():
    backend_database = getDatabase(app.config["DATABASE"])
    cursor = backend_database.execute('select hw_id, hunger, happiness, energy from characters order by hw_id desc')
    character_list = cursor.fetchall()
    character_dict = {}
    if character_list != []:
        character_dict = {'name': character_list[0], 'values': [character_list[1], character_list[2], character_list[3]]}
    return render_template('profile.html', chars=character_dict)


@app.route('/new_char', methods=['POST'])
def new_character():
    db = getDatabase(app.config["DATABASE"])
    db.execute('insert into island_of_misfit_mupets (hw_id, hunger, happiness, energy) values (?, ?, ?, ?)',
                request.form['id'], request.form['hunger'], request.form['happiness'], request.form['energy'])
    db.commit()
    flash("New character added.")
    return "Something"


@app.route('/addCharacter', methods=['POST'])
def add_character():
    if not session.get('logged_in'):
        abort(401)
    db = getDatabase(app.config["DATABASE"])
    # also grab the unassigned characters in connected nodes
    # db.execute('insert into characters (hw_id, hunger, happiness, energy) values (?, ?)',
    #           [request.form[]])
    db.commit()
    flash('Added a new character!')


"""
@app.route('/profile/<nickname>')
def user_profile(nickname):
    # 
"""