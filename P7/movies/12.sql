-- List the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred
SELECT m.title FROM stars AS s1
JOIN stars AS s2 ON s1.movie_id = s2.movie_id
JOIN movies AS m ON m.id = s1.movie_id
WHERE s1.person_id = (
    -- Find the ID of Bradley Cooper
    SELECT p.id FROM people AS p
    WHERE p.name = 'Bradley Cooper'
)
AND s2.person_id = (
    -- Find the ID of Jennifer Lawrence
    SELECT p.id FROM people AS p
    WHERE p.name = 'Jennifer Lawrence'
);
