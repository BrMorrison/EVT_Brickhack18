drop table if exists characters;
create table characters (
    id integer primary key autoincrement,
    hw_id integer not null,
    hunger integer default 0,
    happiness integer default 0,
    energy integer default 0,
    owner integer default 0
);

/*
drop table if exists status_updates;
create table status_updates (
    id integer )
*/
drop table if exists human_users;
create table human_users (
    id integer primary key autoincrement,
    username text not null,
    password text not null,
    death_count integer default 0
);