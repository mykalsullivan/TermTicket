<-- Created by msullivan on 11/18/24.

CREATE OR REPLACE TABLE tickets
(
    ticket_id SERIAL PRIMARY KEY,
    ticket_title VARCHAR(255) NOT NULL,
    ticket_status VARCHAR(50) DEFAULT 'Open',
    ticket_priority VARCHAR(50) DEFAULT 'Medium',
    ticket_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    ticket_updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    ticket_assigned_to VARCHAR(100)
);