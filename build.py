#!/usr/bin/env python3
"""
Script de compilación para Space Invaders
Intenta automatizar la compilación y resolver problemas comunes
"""

import os
import sys
import subprocess
import platform
import json
from pathlib import Path

class SpaceInvadersBuilder:
    def __init__(self):
        self.project_root = Path(__file__).parent
        self.raylib_root = Path("C:/raylib/raylib")
        self.raylib_include = self.raylib_root / "src"
        self.raylib_lib = Path("C:/raylib/w64devkit/x86_64-w64-mingw32/lib")
        self.compiler = Path("C:/raylib/w64devkit/bin/g++.exe")
        self.output = self.project_root / "space-invaders.exe"
        
    def validate_environment(self):
        """Verificar que todas las dependencias existen"""
        print("[*] Validando entorno...")
        
        if not self.compiler.exists():
            print(f"[ERROR] Compilador no encontrado: {self.compiler}")
            return False
        print(f"[OK] Compilador encontrado: {self.compiler}")
        
        if not self.raylib_include.exists():
            print(f"[ERROR] raylib include no encontrado: {self.raylib_include}")
            return False
        print(f"[OK] raylib include encontrado")
        
        if not (self.raylib_lib / "libraylib.a").exists():
            if not (self.raylib_lib / "raylib.lib").exists():
                print(f"[ERROR] libraylib.a no encontrado en {self.raylib_lib}")
                return False
        print(f"[OK] raylib library encontrada")
        
        return True
    
    def compile(self):
        """Intentar compilación con diferentes estrategias"""
        
        src_file = self.project_root / "src" / "main.cpp"
        
        strategies = [
            {
                "name": "Compilación estándar",
                "flags": ["-std=c++17", "-O2"],
            },
            {
                "name": "Sin optimizaciones",
                "flags": ["-std=c++17", "-O0"],
            },
            {
                "name": "Con static libaries",
                "flags": ["-std=c++17", "-static"],
            },
        ]
        
        for strategy in strategies:
            print(f"\n[*] Intentando: {strategy['name']}")
            
            cmd = [
                str(self.compiler),
                *strategy['flags'],
                f"-I{self.raylib_include}",
                f"-L{self.raylib_lib}",
                "-o", str(self.output),
                str(src_file),
                "-lraylib", "-lopengl32", "-lgdi32", "-lwinmm",
            ]
            
            try:
                result = subprocess.run(
                    cmd,
                    capture_output=True,
                    text=True,
                    timeout=120
                )
                
                if result.returncode == 0:
                    print(f"[OK] Compilacion exitosa!")
                    return True
                else:
                    print(f"[X] Fallo con errores:")
                    if len(result.stderr) > 200:
                        print(result.stderr[:200] + "...")
                    else:
                        print(result.stderr)
            
            except subprocess.TimeoutExpired:
                print("[TIMEOUT] Tiempo agotado")
            except Exception as e:
                print(f"[X] Error: {e}")
        
        return False
    
    def run(self):
        """Ejecutar el programa compilado"""
        if self.output.exists():
            print(f"\n[*] Ejecutando: {self.output}")
            try:
                subprocess.run([str(self.output)])
            except Exception as e:
                print(f"[ERROR] No se pudo ejecutar: {e}")
        else:
            print(f"[ERROR] Ejecutable no encontrado: {self.output}")
    
    def build(self):
        """Proceso principal de compilación"""
        print("=" * 55)
        print(" Space Invaders - Sistema de Compilacion")
        print("=" * 55)
        
        if not self.validate_environment():
            print("\n[!] El entorno no esta correctamente configurado.")
            print("Verifique que raylib y w64devkit esten instalados.")
            return False
        
        if not self.compile():
            print("\n[!] La compilacion fallo con todas las estrategias.")
            print("\nIntente manualmente:")
            print(f"  {self.compiler} -std=c++17 \\")
            print(f"    -I{self.raylib_include} \\")
            print(f"    -L{self.raylib_lib} \\")
            print(f"    -o space-invaders.exe src/main.cpp \\")
            print(f"    -lraylib -lopengl32 -lgdi32 -lwinmm")
            return False
        
        print("\n[OK] Compilacion completada exitosamente!")
        print(f"[OK] Ejecutable: {self.output}")
        
        return True

def main():
    if platform.system() != "Windows":
        print("[ERROR] Este script es unicamente para Windows")
        sys.exit(1)
    
    builder = SpaceInvadersBuilder()
    
    if builder.build():
        # Preguntar si ejecutar
        try:
            response = input("\nDesea ejecutar el juego ahora? (s/N): ")
            if response.lower() == 's':
                builder.run()
        except KeyboardInterrupt:
            print("\n[*] Cancelado")
    
    sys.exit(0 if builder.output.exists() else 1)

if __name__ == "__main__":
    main()
