{
  description = "ysyx_workbench";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs,flake-utils }: 
   flake-utils.lib.eachDefaultSystem (system:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
    projectRoot = pkgs.lib.cleanSource ./.;
    my-verilator= (pkgs.verilator.overrideAttrs (oldAttrs: rec {
          version = "5.008"; 
          src = pkgs.fetchFromGitHub {
            owner = "verilator";
            repo = "verilator";
            rev = "v${version}";
            sha256 = "0wqnn2r8kjbrm28c5qajldw5axmrkslds1957wz9r4qfyhd43qpr";
          };
          patches = []; # 禁用所有补丁
        }));
    llvmPackages = pkgs.llvmPackages_18;
    fhsEnv = pkgs.buildFHSUserEnv {
          name = "ysyx-fhs-env";
          targetPkgs = pkgs: with pkgs; [
            # 指定verilator版本为5.008
            my-verilator
            #build-essential
            pkgs.man
            #gcc-doc
            pkgs.git
            pkgs.gdb
            pkgs.readline #libreadline-dev
            pkgs.vim
            pkgs.gcc
            pkgs.python3
            pkgs.SDL2
            pkgs.SDL2_image
            pkgs.SDL2_ttf
            # verilator start
            pkgs.perl
            pkgs.flex
            pkgs.bison
            pkgs.ccache
            pkgs.gperftools
            pkgs.numactl
            # verilator end
            # llvmPackages.llvm
            # llvmPackages.libllvm
            pkgs.llvm_18
            pkgs.pkgsCross.riscv64.buildPackages.gcc
            pkgs.pkgsCross.riscv64.buildPackages.binutils
            # TODO:add more!!!
            # pkgs.ncurses6
            pkgs.ncurses
          ];
          profile = ''
            export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [
              pkgs.ncurses
              pkgs.readline
              pkgs.SDL2
              pkgs.SDL2_image
              pkgs.SDL2_ttf
            # pkgs.llvm_18.llvm-lib  
            ]}:$LD_LIBRARY_PATH
            export CFLAGS="-I${pkgs.ncurses.dev}/include -I${pkgs.readline.dev}/include -I${pkgs.llvm_18.dev}/inlcude $CFLAGS"
            export LDFLAGS="-L${pkgs.ncurses.dev}/lib -L${pkgs.readline.dev}/lib -L${pkgs.llvm_18.dev}/lib $LDFLAGS"
            export CPPFLAGS="-I${pkgs.ncurses.dev}/include -I${pkgs.readline.dev}/include -I${pkgs.llvm_18.dev}/inlcude $CPPFLAGS"
            export PATH=${llvmPackages.llvm}/bin:$PATH
          '';
      runScript = "bash";
        };
        in{
        devShells.default = pkgs.mkShell {
          buildInputs = [ 
            fhsEnv
            pkgs.llvm_18
         ];
          shellHook = ''
            echo "Welcome to ysyx_workbench development environment!"
            echo "Run 'ysyx-fhs-env' to enter the FHS-compatible environment."
          '';
        };
      }
    );
}
  # in {
  #   devShells.${system}.default = pkgs.mkShell {
  #     buildInputs = [
  #       # 指定verilator版本为5.008
  #       my-verilator
  #       #build-essential
  #       pkgs.man
  #       #gcc-doc
  #       pkgs.git
  #       pkgs.gdb
  #       pkgs.readline #libreadline-dev
  #       pkgs.vim
  #       pkgs.gcc
  #       pkgs.python3
  #       pkgs.SDL2
  #       pkgs.SDL2_image
  #       pkgs.SDL2_ttf
  #       # verilator start
  #       pkgs.perl
  #       pkgs.flex
  #       pkgs.bison
  #       pkgs.ccache
  #       pkgs.gperftools
  #       pkgs.numactl
  #       # verilator end
  #       pkgs.llvm_18  
  #       pkgs.pkgsCross.riscv64.buildPackages.gcc
  #       pkgs.pkgsCross.riscv64.buildPackages.binutils
  #       # TODO:add more!!!
  #     ];
  #     shellHook = ''
  #     '';
  #   };

#   };
# }
