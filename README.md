Doc :

https://www.bogotobogo.com/cplusplus/sockets_server_client.php
https://github.com/Dungyichao/http_server
https://trungams.github.io/2020-08-23-a-simple-http-server-from-scratch/
https://www.youtube.com/results?search_query=build+http+server+c%2B%2B
https://beej.us/guide/bgnet/
https://www.digitalocean.com/community/tutorials/understanding-nginx-server-and-location-block-selection-algorithms
https://nginx.org/en/docs/dirindex.html


https://github.com/Dungyichao/http_server

-> 1 Seul argument (.conf)
-> Lire doc. nginx HTTP 1.1 !

-> Match les locations / Blocs serveur {}
-> Plusieurs blocs serveur peuvent listen sur le meme port
-> server_name -> suivant la request choisi le bloc



1. Récuperer info response header et les tester -> Faire fonctionner 
2. Faire en sorte de pouvoir rentrer les combinaisons possibles de ces memes infos
3. Recuperer le request Header et interagir en fonction 
4. Matcher les requirements demandé du server en incorporant les fichiers du .conf
5. finir par les cgi puis parser tte les données



https://nginx.org/en/docs/http/request_processing.html    -> Port / host 

https://nginx.org/en/docs/http/server_names.html	-> server_name


https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page - >error_page


https://www.tecmint.com/limit-file-upload-size-in-nginx/#:~:text=By%20default%2C%20Nginx%20has%20a,http%2C%20server%20or%20location%20context 

https://nginx.org/en/docs/http/ngx_http_core_module.html				-> client body size 


https://docs.nginx.com/nginx/admin-guide/load-balancer/http-load-balancer/.    -> List accepted HTTP


https://www.malekal.com/nginx-faire-une-redirection-301-302-http-vers-https-url/ -> Http redirection

https://docs.nginx.com/nginx/admin-guide/web-server/serving-static-content/ 	-> Directory / file should be searched


https://nginx.org/en/docs/http/ngx_http_autoindex_module.html -> AutoIndex

http://itdoc.hitachi.co.jp/manuals/3020/30203Y1800e/EY180042.HTM#:~:text=There%20are%20three%20ways%20to,handler%20in%20the%20SetHandler%20directive -> CGI







