<-- Created by msullivan on 11/18/24.

CREATE OR REPLACE TABLE tickets
(
    ticket_id SERIAL PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    status VARCHAR(50) DEFAULT 'New',
    priority VARCHAR(50) DEFAULT 'Medium',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    last_updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    assigned_to VARCHAR(100)
);

CREATE OR REPLACE TABLE comments
(
    comment_id SERIAL PRIMARY KEY,
    ticket_id INT NOT NULL,
    author VARCHAR(50) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    last_updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    text TEXT NOT NULL,
    FOREIGN KEY (ticket_id) REFERENCES tickets(ticket_id) ON DELETE CASCADE
);