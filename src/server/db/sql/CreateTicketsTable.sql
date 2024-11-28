-- Created on 11/19/2024 by M.

CREATE TABLE tickets
(
    ticket_id           SERIAL PRIMARY KEY,
    created_at          TIMESTAMP   DEFAULT CURRENT_TIMESTAMP,
    last_updated_at     TIMESTAMP   DEFAULT CURRENT_TIMESTAMP,
    author              VARCHAR(50) NOT NULL,
    title               VARCHAR(255) NOT NULL,
    status              VARCHAR(50) DEFAULT 'New',
    priority            VARCHAR(50) DEFAULT 'Medium',
    assigned_to         VARCHAR(100)
);