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
sha256sums=('9d655902cf3ad2ee6134d146672111e7e2510c28d8c0d10ec02ef5967464ef34')

build() {
  cd "$srcdir/$pkgname-$pkgver"
  make
}

package() {
  install -Dm755 "$srcdir/$pkgname-$pkgver/royal-blocks-gui" "$pkgdir/usr/bin/royal-blocks"
  install -Dm755 "$srcdir/$pkgname-$pkgver/royal-blocks-tui" "$pkgdir/usr/bin/royal-blocks-tui"
  install -Dm644 "$srcdir/$pkgname-$pkgver/royal-blocks-server" "$pkgdir/usr/share/applications/royal-blocks-server"
}