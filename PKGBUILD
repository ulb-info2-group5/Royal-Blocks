pkgname=royal-blocks
pkgver=1.0.0
pkgrel=1
options=(!debug strip)
pkgdesc="A homemade Royal Tetris in C++"
arch=('x86_64')
url="https://github.com/ulb-info2-group5/Tetris-Blocks"
license=('GPL3')
depends=('qt5-base' 'boost')
makedepends=('gcc' 'make' 'cmake' 'boost' 'qt5-base')
source=("royal-blocks.tar.gz")
sha256sums=('0bb7bd56c058cf89fbb721212aad0bb9f2c12faafb64bc7c93212614a937678a')

build() {
  cd "$srcdir/$pkgname-$pkgver"
  make
}

package() {
  install -Dm755 "$srcdir/$pkgname-$pkgver/royal-blocks-gui" "$pkgdir/usr/bin/royal-blocks"
  install -Dm755 "$srcdir/$pkgname-$pkgver/royal-blocks-tui" "$pkgdir/usr/bin/royal-blocks-tui"
  install -Dm644 "$srcdir/$pkgname-$pkgver/royal-blocks-server" "$pkgdir/usr/bin/royal-blocks-server"

  install -Dm644 "$srcdir/royal-blocks.desktop" "$pkgdir/usr/share/applications/royal-blocks.desktop"
  install -Dm644 "$srcdir/royal-blocks-tui.desktop" "$pkgdir/usr/share/applications/royal-blocks-tui.desktop"
  install -Dm644 "$srcdir/royal-blocks-server.desktop" "$pkgdir/usr/share/applications/royal-blocks-server.desktop"
}