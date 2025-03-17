# Get_Next_Line

Because reading a line from a file descriptor is way too tedious.

## Step 1 : undestrand the subject

Le but du projet est d'implémenter une fonction permettant de lire une ligne d'un fichier ou de l'entrée standard (= STDIN = 0), en gérant la mémoire efficacement et en respectant les contraintes imposées par les buffers et les descripteurs de fichiers.

## Step 2 : read and store data

### Step 2.1 : how to read any file

On utilise la fonction ```read()``` pour récupérer un nombre d'octets défini par la macro ```BUFFER_SIZE``` :
- si ```read()``` renvoie 0, on a atteint la fin du fichier
- si ```read()``` renvoie -1, une erreur est survenue
- sinon, on stocke les données lues dans un buffer dynamique.

### Step 2.2 : data storage & buffer management

Le buffer ne doit pas être réinitialisé entre les appels de ```get_next_line()``` pour conserver les données déjà lues mais non encore retournées. D'ou l'utilisation du reste ```static char *remains``` qui correspond a tout ce qui se trouve apres le saut de ligne "\n" trouve dans le buffer.

Concretement, on va concatener les nouveaux morceaux de texte jusqu'à trouver un saut de ligne ("\n") ou atteindre la fin du fichier.

Une fois une ligne complète trouvée, elle est renvoyée, et le reste du buffer (= remains) est conservé pour le prochain appel.

## Step 3 : Extraction d'une ligne complète

Une ligne est considérée comme complète lorsqu'un "\n" est rencontré ou lorsqu'on atteint la fin du fichier.

Une fonction d'extraction parcourt le buffer jusqu'à "\n" et renvoie une sous-chaîne contenant la ligne.

Le buffer est mis à jour en supprimant la ligne extraite, prête à recevoir la prochaine lecture.

## Step 4 : Nettoyage de la mémoire

Pour éviter toute fuite de mémoire, il faut libérer le buffer lorsque la lecture est terminée.

Une fois la dernière ligne retournée, le buffer est également libéré.

Si une erreur survient, il faut libérer le buffer avant de retourner "NULL".

## Step 5 : Bonus (gestion de plusieurs file descriptors)

Le projet bonus demande la gestion de plusieurs descripteurs de fichiers simultanément.

On utilise une structure de stockage distincte pour chaque descripteur de fichier.

Ainsi, chaque appel à ```get_next_line(fd1)``` et ```get_next_line(fd2)``` peut conserver un buffer indépendant pour chaque fichier ouvert.

Avec cette approche, ```get_next_line()``` devient un outil puissant et efficace pour la lecture de fichiers ligne par ligne !
