{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "xv6-riscv-env";

  buildInputs = [
    pkgs.pkgsCross.riscv64-embedded.buildPackages.binutils
    pkgs.pkgsCross.riscv64-embedded.buildPackages.gcc
    pkgs.qemu
    pkgs.gdb
    pkgs.gnumake
    pkgs.python3
  ];

  shellHook = ''
    # Symlink the tools to the exact names xv6 expects
    mkdir -p .nix-tools
    for tool in ar as gcc ld objcopy objdump; do
      ln -sf ${pkgs.pkgsCross.riscv64-embedded.buildPackages.binutils}/bin/riscv64-none-elf-$tool .nix-tools/riscv64-unknown-elf-$tool
    done
    ln -sf ${pkgs.pkgsCross.riscv64-embedded.buildPackages.gcc}/bin/riscv64-none-elf-gcc .nix-tools/riscv64-unknown-elf-gcc
    
    export PATH=$PWD/.nix-tools:$PATH
    export RISCV_PREFIX="riscv64-unknown-elf-"
    echo "xv6-riscv environment ready!"
  '';
}
