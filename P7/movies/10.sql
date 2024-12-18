-- List the names of all people who have directed a movie that received a rating of at least 9.0
/*SELECT DISTINCT p.name
FROM directors AS d
JOIN movies AS m ON d.movie_id = m.id
JOIN ratings AS r ON m.id = r.movie_id
JOIN people AS p ON d.person_id = p.id
WHERE r.rating >= 9.0;*/

SELECT DISTINCT name
FROM people
WHERE id IN
(
    -- Find the names of people with those people IDs
    SELECT person_id
    FROM directors
    WHERE movie_id IN
    (
        -- Find the IDs of people who directed those movies
        SELECT id
        FROM movies
        -- Find the IDs of movies with at least a 9.0 rating
        JOIN ratings ON movies.id = ratings.movie_id
        WHERE ratings.rating >= 9.0
    )
);
