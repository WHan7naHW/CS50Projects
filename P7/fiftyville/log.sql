-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Find a crime scene report on July 28, 2023 and on Humphrey Street
SELECT
    description
FROM
    crime_scene_reports
WHERE
    year = 2023
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street'
    AND description LIKE '%duck%';


-- Find clues from interviews on July 28, 2023 whose transcripts mentions the bakery
SELECT
    transcript
FROM
    interviews
WHERE
    year = 2023
    AND month = 7
    AND day = 28
    AND transcript LIKE '%bakery%';


-- Find a list of suspects: THIEF p1 and ACCOMPLICE p2
SELECT
    p1.id AS thief_id,
    p1.name AS thief_name,
    p.caller AS thief_phone_number,
    p1.passport_number AS thief_passport_number,
    p1.license_plate AS thief_license_plate,
    p2.id AS accomplice_id,
    p2.name AS accomplice_name,
    p.receiver AS accomplice_phone_number,
    p2.passport_number AS accomplice_passport_number,
    p2.license_plate AS accomplice_license_plate
FROM
    phone_calls AS p
JOIN
    people AS p1 ON p.caller = p1.phone_number
JOIN
    people AS p2 ON p.receiver = p2.phone_number
-- Filter people with phone info
WHERE
    p.year = 2023
    AND p.month = 7
    AND p.day = 28
    AND p.duration <= 60
    -- Filter people with car info
    AND p1.license_plate IN (
        -- Find license_plate from bakery_security_logs around 10:15am to 10:25am on July 28, 2023
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
    )
    -- Filter people with ATM info
    AND p1.id IN (
        -- Find person_id from bank_accounts
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE account_number IN (
            -- Find account_number from atm_transactions before 10:15am on July 28, 2023 on Leggett Street who was withdrawing money
            SELECT
                account_number
            FROM
                atm_transactions
            WHERE
                year = 2023
                AND month = 7
                AND day = 28
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw'
        )
    )
;


-- Find the crime with flight info
SELECT
    a1.city AS origin_airport_city,
    a2.city AS destination_airport_city,
    f.year,
    f.month,
    f.day,
    -- Find the earliest flight
    MIN(f.hour) AS hour,
    f.minute,
    p.passport_number AS thief_passport_number,
    p.seat
FROM
    flights AS f
JOIN
    airports AS a1 ON a1.id = f.origin_airport_id
JOIN
    airports AS a2 ON a2.id = f.destination_airport_id
JOIN
    passengers AS p ON p.flight_id = f.id
WHERE
    -- Filter flights from Fiftyville
    a1.city = 'Fiftyville'
    -- Filter flights departing on July 29, 2023
    AND year = 2023
    AND month = 7
    AND day = 29
    -- Filter passengers who are the suspects
    AND p.passport_number IN (3592750733, 5773159633, 3391710505)
;

/* thief_passport_number is 5773159633, so thief is Bruce,
and accomplice is Robin. Destination is New York City.*/
