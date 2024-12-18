-- List the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT p1.name
FROM people AS p1
JOIN stars AS s1 ON s1.person_id = p1.id
JOIN movies AS m1 ON s1.movie_id = m1.id
-- Find the IDs of people associated with those movie IDs
WHERE m1.id IN (
    -- Find the IDs of movies associated with Kevin Bacon’s ID
    SELECT m2.id
    FROM people AS p2
    JOIN movies AS m2 ON s2.movie_id = m2.id
    JOIN stars AS s2 ON s2.person_id = p2.id
    -- Find the ID of Kevin Bacon (the one born in 1958!)
    WHERE p2.name = 'Kevin Bacon' AND p2.birth = 1958
)
-- exclude Kevin Bacon himself from the results
AND p1.name != 'Kevin Bacon';


