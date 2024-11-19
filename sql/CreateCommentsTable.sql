-- Created on 11/19/2024 by M.

CREATE TABLE comments
(
    comment_id          SERIAL PRIMARY KEY,
    ticket_id           INT NOT NULL,
    created_at          TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    last_updated_at     TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    author              VARCHAR(50) NOT NULL,
    text                TEXT NOT NULL,
    FOREIGN KEY (ticket_id) REFERENCES tickets (ticket_id) ON DELETE CASCADE
);