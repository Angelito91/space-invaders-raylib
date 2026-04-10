#!/usr/bin/env python3
"""
Script de compilación para Space Invaders
Compila todos los archivos fuente usando g++ de w64devkit
"""

import os
import sys
import subprocess
import platform
from pathlib import Path
import shutil

class SpaceInvadersBuilder:
    def __init__(self):
        self.project_root = Path(__file__).parent
        self.raylib_root = Path("C:/raylib/raylib")
        self.raylib_include = self.raylib_root / "src"
        self.raylib_lib = Path("C:/raylib/w64devkit/x86_64-w64-mingw32/lib")
        self.gcc = Path("C:/raylib/w64devkit/bin/g++.exe")
        self.gcc_path = "C:/raylib/w64devkit/bin"
        self.output = self.project_root / "space-invaders.exe"
        self.obj_dir = self.project_root / "obj"
        
        self.source_files = [
            "src/main.cpp",
            "src/Game.cpp",
            "src/AssetManager.cpp",
            "src/EntityManager.cpp",
            "src/Entity.cpp",
            "src/Player.cpp",
            "src/Alien.cpp",
            "src/Bullet.cpp",
            "src/BarrierBlock.cpp",
        ]
        
    def validate_environment(self):
        print("[*] Validando entorno...")
        
        if not self.gcc.exists():
            print(f"[ERROR] Compilador no encontrado: {self.gcc}")
            return False
        print(f"[OK] Compilador: {self.gcc}")
        
        if not self.raylib_include.exists():
            print(f"[ERROR] raylib include no encontrado")
            return False
        print(f"[OK] raylib include encontrado")
        
        if not (self.raylib_lib / "libraylib.a").exists():
            print(f"[ERROR] libraylib.a no encontrado")
            return False
        print(f"[OK] raylib library encontrada")
        
        return True
    
    def clean(self):
        print("[*] Limpiando archivos anteriores...")
        if self.output.exists():
            self.output.unlink()
            print(f"[OK] Eliminado: {self.output}")
        
        if self.obj_dir.exists():
            shutil.rmtree(self.obj_dir)
            print(f"[OK] Eliminado directorio: {self.obj_dir}")
    
    def compile_objects(self):
        print("[*] Compilando archivos objeto...")
        
        self.obj_dir.mkdir(exist_ok=True)
        
        for src in self.source_files:
            src_path = self.project_root / src
            obj_name = Path(src).stem + ".o"
            obj_path = self.obj_dir / obj_name
            
            print(f"    Compilando: {src} -> {obj_name}")
            
            cmd = [
                str(self.gcc),
                "-c", str(src_path),
                "-I", str(self.project_root / "include"),
                "-I", str(self.raylib_include),
                "-std=c++17",
                "-O2",
                "-o", str(obj_path)
            ]
            
            try:
                result = subprocess.run(
                    cmd,
                    capture_output=True,
                    text=True,
                    timeout=60
                )
                
                if result.returncode != 0:
                    print(f"[ERROR] Error compilando {src}:")
                    print(result.stderr)
                    return False
                    
            except subprocess.TimeoutExpired:
                print(f"[ERROR] Timeout compilando {src}")
                return False
        
        print("[OK] Todos los archivos compilados")
        return True
    
    def link(self):
        print("[*] Enlazando ejecutable...")
        
        obj_files = list(self.obj_dir.glob("*.o"))
        if not obj_files:
            print("[ERROR] No se encontraron archivos objeto")
            return False
        
        obj_args = [str(f) for f in obj_files]
        
        cmd = [
            str(self.gcc),
            *obj_args,
            "-o", str(self.output),
            "-L", str(self.raylib_lib),
            "-lraylib",
            "-lopengl32", "-lgdi32", "-lwinmm", "-luser32", "-lshell32"
        ]
        
        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=60
            )
            
            if result.returncode != 0:
                print("[ERROR] Error enlazando:")
                print(result.stderr)
                return False
                
        except subprocess.TimeoutExpired:
            print("[ERROR] Timeout enlazando")
            return False
        
        print(f"[OK] Ejecutable creado: {self.output}")
        return True
    
    def build(self):
        print("=" * 50)
        print(" Space Invaders - Compilacion")
        print("=" * 50)
        
        if not self.validate_environment():
            return False
        
        self.clean()
        
        if not self.compile_objects():
            return False
        
        if not self.link():
            return False
        
        print("\n" + "=" * 50)
        print(" COMPILACION EXITOSA!")
        print(f" Ejecutable: {self.output.absolute()}")
        print("=" * 50)
        
        return True
    
    def run(self):
        if self.output.exists():
            print(f"\n[*] Ejecutando juego...")
            try:
                subprocess.run([str(self.output)])
            except KeyboardInterrupt:
                print("\n[*] Juego cerrado")
        else:
            print("[ERROR] Ejecutable no encontrado")

def main():
    if platform.system() != "Windows":
        print("[ERROR] Este script es solo para Windows")
        sys.exit(1)
    
    builder = SpaceInvadersBuilder()
    
    if builder.build():
        response = input("\nEjecutar el juego? (s/N): ")
        if response.lower() == 's':
            builder.run()
    
    sys.exit(0 if builder.output.exists() else 1)

if __name__ == "__main__":
    main()
