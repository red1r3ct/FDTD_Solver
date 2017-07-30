export const checkAuth = async () => {
	try {
		const res = await fetch('/api/auth/', {credentials: 'include'});
		const body = await res.json();
		if (body.error) {
			return {res: null, err: {reason: "Not allowed"}}
		}
		return {res: body, err: null}
	} catch (err) {
		return {res: null, err}
	}
};