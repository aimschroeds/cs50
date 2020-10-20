select count(m.title) AS rated_10
from movies m
left join ratings r ON m.id = r.movie_id
where r.rating = 10.0;