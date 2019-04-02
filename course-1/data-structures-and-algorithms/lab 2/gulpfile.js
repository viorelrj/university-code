const { src, dest, series, parallel, watch } = require('gulp')
const browsersync = require('browser-sync')

function browserSync(done) {
	browsersync.init({
		server: {
			baseDir: "src/"
		},
		port: 3000
	});
	done();
}

function watchFiles() {
	watch(["src/js/*.js", "src/*.html"], browserSyncReload);
}

// BrowserSync Reload
function browserSyncReload(done) {
	browsersync.reload();
	done();
}

exports.sync = browserSync
exports.watch = watchFiles
exports.dev = series(browserSync, watchFiles)