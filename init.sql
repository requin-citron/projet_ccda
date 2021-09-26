CREATE TABLE IF NOT EXISTS clients (
    email TEXT PRIMARY KEY,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    enterprise TEXT,
    phone INTEGER ,
    photo TEXT,
    dt datetime default current_timestamp
);

CREATE TABLE IF NOT EXISTS history (
    email TEXT PRIMARY KEY,
    dt datetime default current_timestamp
);
