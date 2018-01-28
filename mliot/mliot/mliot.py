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
    character_data = cursor.fetchall()
    # print(tuple(character_list[0]))
    character_list = []
    for datum in character_data:
        character_list += [{'id':tuple(datum)[0], 'hunger':tuple(datum)[1], 'happiness':tuple(datum)[2], 'energy':tuple(datum)[3]}]
    return render_template('profile.html', chars=character_list)

@app.route('/node')
def node_profile():
    db = getDatabase(app.config["DATABASE"])
    cursor = db.execute('select hw_id, hunger, happiness, energy from characters order by hw_id desc')
    char_list = cursor.fetchall()
    return render_template('node.html', chars=char_list, owner="Test")

@app.route('/new_char', methods=['GET', 'POST'])
def new_character():
    # first check if the char is already in our character table
    db = getDatabase(app.config["DATABASE"])

    # get the values from the request
    my_id = int(request.args.get('id'))
    my_hunger = int(request.args.get('hunger'))
    my_happiness = int(request.args.get('happiness'))
    my_energy = int(request.args.get('energy'))

    cursor = db.execute('select hw_id from characters')
    id_data = cursor.fetchall()
    id_list = []
    for datum in id_data:
        id_list += [tuple(datum)[0]]
    if my_id in id_list:
        # don't add it, update instead
        print("Old id, updating")
        db.execute("""update characters
                      set hunger = (?),
                          happiness = (?),
                          energy = (?)
                      where hw_id = (?);""",
                   my_hunger, my_happiness, my_energy, my_id)
    else:
        print("New id, adding it")
        db.execute('insert into characters (hw_id, hunger, happiness, energy) values (?, ?, ?, ?)',
                   [my_id, my_hunger, my_happiness, my_energy])
    db.commit()
    flash("New character added.")
    return redirect(url_for('user_profile'))


@app.route('/test_query', methods=['GET', 'POST'])
def test_query_capture():
    test = request.args.get('test')
    print(test)
    return redirect(url_for('news_feed'))


@app.route('/addCharacter', methods=['POST'])
def add_character():
    # if not session.get('logged_in'):
    #    abort(401)
    db = getDatabase(app.config["DATABASE"])
    # also grab the unassigned characters in connected nodes
    db.execute('insert into characters (hw_id, hunger, happiness, energy) values (?, ?, ?, ?)',
              [request.form['id'], request.form['hunger'], request.form['happiness'], request.form['energy']])
    db.commit()
    flash('Added a new character!')


"""
@app.route('/profile/<nickname>')
def user_profile(nickname):
    #
"""
