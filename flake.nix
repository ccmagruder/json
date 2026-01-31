# flake.nix
{
  description = "Professional CUDA C++ Project Entry Point";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
      };
    in {
      # 1. The Package: Allows 'nix build'
      packages.${system}.default = pkgs.callPackage ./default.nix { };

      # 2. The Dev Shell: Allows 'nix develop'
      devShells.${system}.default = pkgs.mkShell {
        # 'inputsFrom' pulls all tools and libs from default.nix!
        # No need to repeat gcc, cmake, or gtest here.
        inputsFrom = [ self.packages.${system}.default ];

        buildInputs = with pkgs; [
          ccls
          zsh
        ];

        shellHook = ''
          export PS1="(json) $PS1"
          echo "🚀 Environment ready. Run 'cmake -B build' to begin."
          exec ${pkgs.zsh}/bin/zsh
        '';
      };
    };
}
