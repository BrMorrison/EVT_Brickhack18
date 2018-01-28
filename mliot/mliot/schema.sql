drop table if exists characters;
create table characters (
    id integer primary key autoincrement,
    hw_id integer not null,
    hunger integer not null,
    happiness integer not null,
    energy integer not null
);

drop table if exists human_users;
create table human_users (
    id integer primary key autoincrement,
    username text not null,
    password text not null,
    death_count integer not null
);