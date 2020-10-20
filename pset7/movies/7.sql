select m.title, r.rating
from movies m
LEFT JOIN ratings r ON m.id = r.movie_id
WHERE r.rating != '\N' and m.year = 2010
ORDER BY r.rating DESC, m.title;