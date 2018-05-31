# Projet RéVA: Analyse 3D de la marche
Repo/Rapport du binôme Dylan Dia - Benjamin Betti pour le projet de ReVA 4A portant sur l'étude de la marche.
Le rapport complet se trouve sur le [wiki](https://github.com/Fra-592/Projet-ReVA-Etude-de-la-marche/wiki) du repository.

## Workflow
Pour obtenir nos résultats, nous avons suivi les étapes suivantes sur les fichiers contenus dans le dossier `points`, au format .ply ASCII, avec les informations de couleurs évoquées précédemment:
1. Nettoyage manuel des points aberrants des frames (ceux situés sous les pieds et/ou totalement hors du corps), puis export au format .ply ASCII, en conservant les données de couleurs.
2. Création automatique des normales via Meshlab (`Filters -> Point Set -> Compute normals for point sets`), puis export au format .ply ASCII, en conservant les données de couleurs et les normales.
3. Redressement des normales en fonction de la couleur du point associé afin qu'elles pointent vers l'intérieur du corps (cf script `normales-correction`).
    * Utilisation: compilation simple avec `g++ normales-corrections.cpp -o exe` puis utilisation de la forme `./exe <chemin vers la frame à traiter>`. Produit un fichier `parsed.ply` qui contient les normales redressées, au format .ply ASCII avec couleurs et normales.
4. Application d'un screened poisson via Meshlab (`Filters -> Remeshing, Simplification and Reconstruction -> Surface Reconstruction: Screened Poisson`). Export au format .ply binaire sans conservation des couleurs ou normales.
5. Calcul des cartes de courbure via Meshlab (`Filters -> Color Creation and Processing -> Discrete Curvatures`). Captures d'écran pour chaque frame pour créer les animations.
6. Création des animations sous Blender.
    * Pour séquencer les images: Passer le panneau du bas en mode `Video Sequence Editor`, puis faire `Add -> Image`, sélectionner toutes les images concernées puis cliquer sur `Add Image Strip`.
    * Pour faire le rendu: Passer le panneau du milieu en mode `Properties`, régler le `Frame Rate` en fonction de la vitesse désirée, choisir le fichier de sortie désiré dans la section `Output` puis cliquer sur le bouton `Animation`.

**Remarques:** 
* _Toutes les opérations sous Meshlab ont été effectuées avec les paramètres par défaut._
* _La 1ère étape peut facilement être automatisée, notamment en parsant les coordonnées des points lorsqu'ils sont enregistrés au format .ply ASCII pour supprimer les aberrations._

## Organisation du repository
* Le dossier `points` contient les 100 frames de la marche normale, avec les informations de couleur.
* Le dossier `cleared` contient ces mêmes frames, débarassées manuellement sous Meshlab des points aberrants au niveau des pieds.
* Le dossier `normales` contient les frames du dossier précédent, avec des normales calculées par Meshlab puis redressées par le script `normales-correction`.
* Le dossier `meshes` contient les frames du marcheur reconstruit, sur lequel on peut calculer les différentes courbures. Les points d'origine ne sont plus présents dans ce dossier, et les informations de couleur en sont également absentes.
* Les dossiers `*_back` et `*_front` contiennent des captures d'écran des courbures spécifiées dans le nom du dossier sur chacune des frames, ainsi que les animations résultantes.
* Le dossier `scripts` contient les scripts permettant un redressement basique des normales ou une séparation du dos et de la face du marcheur. Attention toutefois, dans le cas de ce second script, il faudra mettre à jour le nombre de points dans chacun des fichiers générés.
