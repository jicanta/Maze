// basic promise class for resolving asynchronous issues

const STATUS = {
	PENDING: 0,
	RESOLVED: 1,
	REJECTED: 2,
}

class Pact {
	constructor(executor) {
		this.thenFuncs = [];
		this.catchFuncs = [];
		this.status = STATUS.PENDING;

		this.resolve = (val) => {
			this.status = STATUS.RESOLVED;
			this.resolvedVal = val;
			this.thenFuncs.forEach((func) => func(val));
		}

		this.reject = (val) => {
			this.status = STATUS.REJECTED;
			this.rejectedVal = val;
			this.catchFuncs.forEach((func) => func(val));
		}

		executor(this.resolve, this.reject);
	}

	catch(catchFunc) {
		if(this.status === STATUS.PENDING) {
			this.catchFuncs.push(catchFunc);
		}

		if(this.status === STATUS.REJECTED) {
			catchFunc(this.rejectedVal);
		}
	}

	then(thenFunc) {
		if(this.status === STATUS.PENDING) {
			return new Pact((resolve, reject) => {
				this.thenFuncs.push((val) => {
					resolve(thenFunc(val));
				});
			});
		}

		if(this.status === STATUS.RESOLVED) {
			thenFunc(this.resolvedVal);
		}
	}
}

module.exports = Pact;