# Étude de l'équation de Rayleigh-Stokes

Ce dépôt contient les travaux réalisés dans le cadre du travail encadré de recherche (TER) du **Master 1 MANU** (Modélisation et Analyse Numérique), à la **Faculté des Sciences de l'Université de Montpellier**.

## 📝 Présentation du projet
L'objectif de ce travail était d'étudier l'équation de Rayleigh–Stokes, qui permet notamment de modéliser le comportement de fluides viscoélastiques. Dans un premier temps, on introduit le modèle et on dérive les équations de Rayleigh–Stokes scalaire et vectorielle en dimension quelconque. Dans un deuxième temps, on réalise une étude mathématique de ces équations, en utilisant notamment une approche par transformée de Fourier ainsi qu'une formulation variationnelle. Dans un troisième temps, on s'intéresse à l'approximation numérique de l'équation scalaire par une méthode de différences finies, dont on étudie la consistance, la stabilité et la convergence. Plusieurs simulations numériques sont ensuite réalisées, notamment en comparaison avec l'équation de la chaleur. Enfin, on introduit une approximation par la méthode de Galerkin discontinu et on étudie les premières propriétés de ce schéma numérique.

## 📁 Contenu du dépôt
* `rapport` : Le code Latex complet du rapport, avec notamment la version finale du rapport au format pdf.
* `presentation` : Le code Latex complet du diaporama réalisé pour la présentation du projet, avec la version finale au format pdf.
* `code` : Un dossier `python` contenant un notebook jupyter avec de nombreux codes et graphiques utilisés dans le rapport. Un dossier `cpp` contenant une version du schéma différence finie permettant de résoudre l'équation de Rayleigh-Stokes en C++.

## 👥 Équipe
* **Hugo Johnson**
* **Quentin Lahaye**
* Sous la direction du **Dr. Fabien Marche**.