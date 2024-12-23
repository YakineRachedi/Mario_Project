# Projet Mario - Implémentation en C++ avec SDL2  

Ce projet, réalisé en binôme avec **Sarah Berkane**, propose une implémentation simple en C++ d’un jeu inspiré de Mario, en utilisant la bibliothèque graphique **SDL2**.  

- **Mario** est représenté par un carré rouge.  
- **Les ennemis** (tortue ou carapaceur) sont représentés par des carrés verts.  
- **Les obstacles** sont représentés par des carrés noirs.  

## Prérequis  

### 1. Installation des bibliothèques externes  
- **SDL2**  
- **SDL2_ttf**  

### 2. Utilisation avec CMake  
Si vous souhaitez utiliser **CMake**, voici les étapes :  
1. Créez un dossier `build` :  
   ```bash
   mkdir build && cd build
   ```  
2. Exécutez la commande suivante :  
   ```bash
   cmake ..
   ```  
   **Important :** Vous devez modifier les fichiers `CMakeLists.txt` pour préciser le chemin absolu vers la bibliothèque **SDL2_ttf**. Par exemple, changez cette ligne :  
   ```cmake
   set(SDL2_TTF_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2")
   ```  
   Remplacez le chemin par celui correspondant à votre installation. **SDL2** sera automatiquement détectée par `find_package()`.  

### 3. Utilisation avec Makefile  
Si vous préférez utiliser le **Makefile**, modifiez les deux lignes suivantes pour indiquer les chemins corrects :  
   ```makefile
   SDL2_TTF_INCLUDE = /opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2  
   SDL2_TTF_LIB = /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib  
   ```  
   Vous devrez également installer **pkg-config** pour détecter correctement les bibliothèques SDL2.  

### 4. Remarque pour les utilisateurs de macOS  
Si vous utilisez macOS, il n’est généralement pas nécessaire de modifier ces chemins.  

---

**Bon jeu !** 🎮  

---
