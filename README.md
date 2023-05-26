# Partie 1 - Approches basiques

## Batiste Laloi

### Les problématiques :

- Remonter les informations de contrôle (start/stop sur un équipement)
- Remonter d'information sporadique (appuie bumper)
- Remonter de flux d'information (flux vidéo, flux audio)

### Enoncé : 

Montrer comment on peut répondre aux problématiques avec une approche à base de :
- UDP
- TCP

Faites un comparatif, proposer des codes permettant d’envoyer des données (remonté capteur et informations de contrôle) et permettant le transfert d’images. Concernant les images, on se posera aussi la question de la mise en place de traitement et de mise en chaine de ces différents traitements. Tout cela sous forme de README(s) (markdown) et de code d’exemples sur github

#### UDP : 

Je vais utiliser le langage de programmation C pour réaliser les codes.

##### Remonter les informations de contrôle (start/stop sur un équipement) :

###### Client :
