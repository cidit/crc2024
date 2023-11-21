# Compétition de Programmation Kryptik 2024

Bienvenue à la Compétition de Programmation Kryptik 2024 ! Pour vous aider dans cette compétition, ce guide vous aidera à configurer votre environnement de développement, comprendre la structure de la compétition et respecter le code de conduite.

## Configuration de votre Environnement
Avant de plonger dans les problèmes, il est essentiel de configurer votre environnement de développement pour vous assurer que votre code s'exécute dans les mêmes conditions que celui des autres participants. Voici les directives étape par étape pour vous aider à démarrer.

1. **Installer Miniconda ou Anaconda** :
Si vous n'avez pas Conda de déjà installé sur votre système, vous devrez le faire. Selon vos préférences, vous pouvez choisir soit :
- [Miniconda](https://docs.conda.io/projects/miniconda/en/latest/miniconda-install.html) (Léger, uniquement les packages nécessaires).
- [Anaconda](https://docs.anaconda.com/free/anaconda/install/index.html) (Complet, inclut de nombreux outils Python, bibliothèques, une interface en ligne de commande, et plus).

2. **Obtenir les Fichiers de la Compétition** :
Assurez-vous d'avoir tous les fichiers nécessaires, y compris `kryptik_2024_env.yml`, car il contient la configuration d'environnement requise.

3. **Créer l'Environnement Conda** :
Accédez au répertoire contenant `kryptik_2024_env.yml` et exécutez :
```
conda env create -f `kryptik_2024_env.yml`
```
**Note** : La création de l'environnement peut prendre un certain temps.

4. **Activer l'Environnement** :
Chaque fois que vous travaillez sur la compétition, assurez-vous d'activer l'environnement avec :
```
conda activate kryptik_2024_env
```

## Résolution des Problèmes
Avec l'environnement activé, vous pouvez maintenant travailler sur les problèmes de la compétition.

- **Tester Votre Solution** : Utilisez `pytest` pour évaluer vos solutions. Exemple :
```
pytest test_nom_fichier.py
```
Par exemple, pour tester votre solution pour le premier problème, vous exécuteriez :
```
pytest test_partie_1.py
```
**Note** : Réussir les tests fournis est seulement le début. Nos tests d'évaluation complets couvrent des scénarios supplémentaires, alors pensez aux cas limites dans votre solution.

## Structure de Fichiers et Aperçu
Le répertoire `CRC_2024_KRYPTIK_PRELIM_1` a été structuré pour offrir une clarté et une facilité de navigation. Voici un aperçu :

- **README_FR.md** : Ce document même ! Contient des instructions, des informations générales sur la compétition et des directives sur l'utilisation des fichiers fournis.

- **Prelim1_FR.pdf** : Contient les questions des problèmes en français.

- **Prelim1_EN.pdf** : Contient les questions des problèmes en anglais.

- **kryptik_2024_env.yml** : Le fichier d'environnement Conda. Ce fichier contient les spécifications de l'environnement Python que vous devez utiliser pour assurer la cohérence et la compatibilité du code.

- **Prelim1/** : Ce répertoire contient tous les ensembles de problèmes individuels pour la compétition.
    - **part_1** (et des répertoires similaires pour les problèmes suivants) :
        - **part_1.py** : Un fichier template en Python où vous allez écrire ou compléter le code pour le problème. Ce template peut contenir un code de base comme exemple ou des fonctions pour vous aider.
        - **test_part_1.py** : La suite de tests abrégée pour `part_1.py`. Vous pouvez l'utiliser pour tester votre solution à l'aide d'un ensemble de tests prédéfinis. Notez que lors de l'évaluation de vos solutions, notre suite de tests testera plus de cas que seulement ceux dans la suite de tests donnée.

## Directives de Soumission
### Préparation de Votre Solution
Lorsque vous avez terminé les problèmes et êtes prêt à soumettre, veuillez suivre ces étapes :
1. **Intégrité des Fichiers** : Ne supprimez ni ne renommez aucun fichier du répertoire `CRC_2024_KRYPTIK_PRELIM_1`.
2. **Compression** : Compressez l'ensemble du répertoire `CRC_2024_KRYPTIK_PRELIM_1`. Assurez-vous que le fichier zip conserve la structure du répertoire.
3. **Soumission** : Envoyez le dossier compressé via le lien Google Drive fourni dans votre kit de participant. Si vous n'avez pas le lien, demandez à votre mentor les informations du kit du participant et contactez si nécessaire CRC.Frank ou CRC.Louis sur Discord.

Une seule soumission (fichier zip) sera acceptée par école.

## Code de Conduite & Intégrité
Maintenir l'intégrité et suivre le code de conduite est primordial.
- **Travail fait par les participants** : Toutes les solutions soumises doivent être votre propre travail.
- **Pas de Plagiat** : Copier des solutions, que ce soit celles d'autres participants ou provenant de sources en ligne, est strictement interdit. Tout participant qui s'est fait prendre à faire du plagiat sera disqualifié.
- **Pas de Partage de Solutions** : Ne partagez pas vos solutions, ne discutez pas des techniques de résolution de problèmes et ne donnez pas d'indices aux autres équipes pendant la compétition.
- **Utilisation de Libraries** : Sauf s'il est explicitement mentionné autrement, l'utilisation de librairies, outils ou services en ligne (autres que pour la configuration de l'environnement ou la référence à la documentation) n'est pas autorisée. Consultez les règlements officiels (Section 4.3.1) pour les librairies autorisées et si vous avez des doutes, demandez dans le canal Discord CRC dédié aux questions de programmation.

Rappelez-vous, l'essence de cette compétition est d'apprendre, de se dépasser soi-même et d'améliorer sa capacité de résolution de problèmes grâce à la programmation. Enfreindre le code de conduite n'affecte pas seulement votre capacité à apprendre de ces problèmes, mais aussi l'intégrité de l'esprit de compétition équitable entre le différentes équipes.

## Foire Aux Questions (FAQ)

### Que faire si je rencontre des problèmes lors de l'installation de Miniconda ou Anaconda?
Tout d'abord, assurez-vous de suivre les guides d'installation officiels de [Miniconda](https://docs.conda.io/projects/miniconda/en/latest/miniconda-install.html) ou [Anaconda](https://docs.anaconda.com/free/anaconda/install/index.html). Si les problèmes persistent, votre meilleur allié est une bonne session de recherche sur Google, où de nombreuses réponses peuvent être trouvées. Si rien ne fonctionne, n'hésitez pas à nous demander de l'aide.

### Y a-t-il des restrictions sur les langages de programmation que nous pouvons utiliser?
Cette année, pour Kryptik 2024, le seul langage de programmation autorisé est Python. Plus précisément, vous utiliserez Python 3.10 comme spécifié dans l'environnement Conda.

### Pouvons-nous utiliser des bibliothèques ou modules externes dans notre solution?
Sauf mention explicite dans un énoncé de problème, l'utilisation de bibliothèques et de modules externes n'est pas autorisée. L'accent est mis sur l'utilisation des bibliothèques standard de Python pour résoudre les problèmes. Si l'utilisation d'une bibliothèque externe est autorisée, elle se trouvera déjà dans l'environnement Conda fourni. Vous pouvez consulter le règlement officiel (Section 4.3.1) pour plus d'informations.

### Que se passe-t-il si nous manquons la date limite de soumission?
Les soumissions reçues après la date limite ne seront pas éligibles pour être évaluées. Nous encourageons toutes les équipes à soumettre leur travail bien avant la date limite pour éviter tout problème de dernière minute.

### Comment notre code sera-t-il évalué?
Les soumissions de code sont évaluées en fonction de la correction, de l'efficacité, du respect des exigences du problème et de la lisibilité du code. Nous utilisons également une suite complète de tests, y compris ceux fournis, pour assurer la robustesse.

### Pouvons-nous mettre à jour notre soumission?
Vous pouvez mettre à jour votre soumission autant de fois que vous le souhaitez avant la date limite. Seule la dernière soumission sera prise en compte pour l'évaluation.

### Que faire si nous trouvons une erreur dans l'énoncé du problème?
Si vous pensez qu'il y a une erreur dans l'énoncé du problème, veuillez nous contacter immédiatement. Nous examinerons la question et fournirons des clarifications ou des corrections si nécessaire.

### Comment pouvons-nous nous préparer pour la compétition?
Familiarisez-vous avec Python, les concepts d'informatique et assurez-vous de comprendre l'utilisation de `pytest` pour tester vos solutions.

### Je ne sais pas comment programmer en Python, par où dois-je commencer?
Ne vous inquiétez pas, Internet regorge de ressources incroyables pour apprendre la programmation. Une que nous recommandons vivement est celle de [freeCodeCamp](https://www.youtube.com/watch?v=eWRfhZUzrAc&list=PLWKjhJtqVAbnqBxcdjVGgT3uVR10bzTEB) sur YouTube.
