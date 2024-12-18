-- List the names of all people who starred in a movie released in 2004, ordered by birth year
/* Alternatively:
SELECT DISTINCT(p.name)
FROM people AS p
JOIN stars AS s ON p.id = s.person_id
JOIN movies AS m ON s.movie_id = m.id
WHERE m.year = 2004
ORDER BY p.name, p.birth;
>>>
:( 9.sql produces correct result
    expected "Craig T. Nelso...", not "Craig T. Nelso..."
???
*/

SELECT DISTINCT name
FROM people
WHERE id IN
(

    SELECT person_id
    FROM stars
    WHERE movie_id IN
    (

        SELECT id
        FROM movies
        WHERE year = 2004
    )
)
ORDER BY birth;
